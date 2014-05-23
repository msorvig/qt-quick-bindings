#include "introspection_objc.h"
#include <QtCore/QtCore>
#include <QtCore/private/qmetaobjectbuilder_p.h>

#include <Cocoa/Cocoa.h>
#include <objc/runtime.h>

#include <RTProperty.h>
#include <RTMethod.h>

namespace ObjCIntrospection
{

// "extra" meta information. Would ideally go into a
// QMetaObject subclass.
class ExtraMetaObject
{
public:
    QHash<QByteArray, int> propertyIndexes; // property name -> index
    QHash<int, bool> isSynthesizedProerty; // index -> isSynth.
};

typedef QHash<Class, ExtraMetaObject*> ExtraMetaObjectStore; // Objc Class -> ExtraMetaObject
Q_GLOBAL_STATIC(ExtraMetaObjectStore, extraMetaObjects);

static int g_debug = -1;
bool debug()
{
    if (g_debug == -1)
        g_debug = qgetenv("QT_OBJC_INTROSPECTION_DEBUG").toInt();
    return g_debug;
}

template <typename C, typename P>
C filter(const C &sequence, P predicate) {
    C result;
    auto it = sequence.begin();
    while (it != sequence.end()) {
        if (predicate(*it))
            result.append(*it);
    }
    return result;
}

Class classForName(NSString *className)
{
    return NSClassFromString(className);
}

NSArray *subclasses(NSString *className)
{
    return [classForName(className) rt_subclasses];
}

BOOL isPublicClass(id klass)
{
    const char * className = class_getName(klass);
    return !QByteArray(className).startsWith('_');
}

NSArray * publicClasses(NSArray *classes)
{
    return [classes objectsAtIndexes:[classes indexesOfObjectsPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
        Q_UNUSED(idx);
        Q_UNUSED(stop);
        return isPublicClass(obj);
    }]];
}

BOOL isNSObjectSubclass(Class klass)
{
    return [klass isSubclassOfClass: [NSObject class]];
}

BOOL isNSObjectSubclass(NSString *className)
{
    return isNSObjectSubclass(classForName(className));
}

QList<QByteArray> classNames(NSArray *classes)
{
    QList<QByteArray> names;
    for (id klass in classes) {
        const char * className = class_getName(klass);
        if (!className)
            continue;
        names.append(QByteArray(className));
    }
    return names;
}

QList<QByteArray> nsobjectClassNames()
{
    return classNames(publicClasses(subclasses(@"NSObject")));
}

QList<QByteArray> nsviewClassNames()
{
    return classNames(publicClasses(subclasses(@"NSView")));
}

bool isNSView(const QByteArray className)
{
    Class klass = NSClassFromString(QString(className).toNSString());
    return [klass isSubclassOfClass: [NSView class]];
}

// Map Objective-C type to Qt Type
NSString *mapTypeName(NSString *type)
{
    // Seen type names:
    // T = "@\"NSMutableArray\""
    // T = "@?";                    _animationFinishedHandler
    // T = c;                       BOOL
    // T = "@";
    // T = "{CGRect={CGPoint=dd}{CGSize=dd}}";
    // T = d;
    //https://developer.apple.com/library/mac/documentation/cocoa/conceptual/ObjCRuntimeGuide/Articles/ocrtTypeEncodings.html

    //NSLog(@"mapTypeName %@", type);

    // basic types
    NSDictionary *typeMap = @{
        @"c" : @"bool",         // "char" or "bool", but in practice "bool" in the Cocoa class APIs
        @"s" : @"short",
        @"l" : @"long",
        @"q" : @"long long",
        @"C" : @"unsigned char",
        @"S" : @"unsigned short",
        @"L" : @"unsigned long",
        @"Q" : @"unsigned long long",
        @"f" : @"float",
        @"d" : @"double",
        @"v" : @"void",
        @"*" : @"char *",
    };
    NSString *value = [typeMap objectForKey : type];
    if (value != nil)
        return value;

    // strings
    if ([type isEqualToString:@"@\"NSString\""])
        return @"QString";

    // selectors. Can use strings/byte arrays, as long as
    // NSSelectorFromString is called on use
    if ([type isEqualToString:@":"])
        return @"QString";

    if ([type isEqualToString:@"{CGPoint=dd}"])
        return @"QPointF";

    if ([type isEqualToString:@"{CGSize=dd}"])
        return @"QSizeF";

    if ([type isEqualToString:@"{CGRect={CGPoint=dd}{CGSize=dd}}"])
        return @"QRectF";

    // catch-all for NSObject subclasses.
    if ([type hasPrefix:@"@"])
        return @"NSObject *";

    return nil;
}

id convertValue(const QVariant &value)
{
    // ### mix of QVariant::Type and QMetaType::Type
    switch (value.type()) {
        case QVariant::String:
            return value.toString().toNSString();
        break;
        case QVariant::Bool:
            return [NSNumber numberWithBool: value.toBool()];
        break;
        case QVariant::Int:
            return [NSNumber numberWithInt: value.toInt()];
        break;
        case QVariant::UInt:
            return [NSNumber numberWithUnsignedInt: value.toUInt()];
        break;
        case QVariant::LongLong:
            return [NSNumber numberWithLongLong: value.toLongLong()];
        break;
        case QVariant::ULongLong:
            return [NSNumber numberWithUnsignedLongLong: value.toULongLong()];
        break;
        case QVariant::Double:
            return [NSNumber numberWithDouble: value.toDouble()];
        break;
//      (this is QChar not char)
//        case QVariant::Char:
//            return [NSNumber numberWithChar: value.toChar()];
//        break;
        case QMetaType::Float:
            return [NSNumber numberWithFloat: value.toFloat()];
        break;
        case QVariant::Url:
            return value.toUrl().toNSURL();
        break;
        case QMetaType::QObjectStar: {
            QObject *object = qvariant_cast<QObject *>(value);
            return nil;
        break; }
        case QMetaType::VoidStar:
            return (id)qvariant_cast<void *>(value);
        break;
        default: break;
    }

    qDebug() <<"### convertValue unknown type" << value.type() << value.typeName();

    return nil;
}

QVariant convertValue(id value)
{
    qDebug() <<"unimplemented QVariant convertValue(id value)";
    return QVariant();
}

QList<Property> mergeProperties(const QList<Property> &a, const QList<Property> &b)
{
    const QList<Property> &largest = a.count() > b.count() ? a : b;
    const QList<Property> &smallest = a.count() > b.count() ? b : a;

    QList<Property> finalProperties = largest;
    // horrible, Horrible! O(n^2) merge.
    foreach(Property p, smallest) {
        bool found = false;
        foreach(Property q, largest) {
            if (p.name == q.name) {
                found = true;
                break;
            }
        }
        if (!found)
            finalProperties.append(p);
    }
    return finalProperties;
}


QList<Property> classProperties(const QByteArray className)
{
    QList<Property> properties;
    Class klass = classForName(QString(className).toNSString());
    for (id object in [klass rt_properties]) {
        RTProperty *property = static_cast<RTProperty *>(object);

        // skip private "underscore" properties. ### are there any?
        if ([[property name] hasPrefix:@"_"])
             continue;

         // The "T" attribute has the type string. Map it to a C++/Qt type.
         NSString *type = mapTypeName([[property attributes] valueForKey:@"T"]);

         // skip unknown types
         if (type == nil) {
            if (debug())
                qDebug() << "Skip property" << QString::fromNSString([property name])
                         << "Unknown type" << QString::fromNSString(type);
            continue;
         }

        Property newProperty;
        newProperty.name = QString::fromNSString([property name]).toLatin1();
        newProperty.type = QString::fromNSString(type).toLatin1();
        properties.append(newProperty);
    }

    return properties;
}


QList<Method> classMethods(const QByteArray className)
{
    Class klass = classForName(QString(className).toNSString());
    NSMutableArray *methods = [NSMutableArray arrayWithArray:[klass rt_methods]];

    QList<Method> _methods;

    for (id object in methods) {
        RTMethod *method = static_cast<RTMethod *>(object);
        NSString *selectorName = [method selectorName];

        // Skip private methods starting with "_"
        if ([selectorName hasPrefix:@"_"] ||
            [selectorName rangeOfString:@"__"].location != NSNotFound) {
            continue;
        }

        // Skip any method that conintains "_" (private?)
        if ([selectorName rangeOfString:@"_"].location != NSNotFound) {
            continue;
        }

        // Get the signature. instanceMethodSignatureForSelector throws exceptions on
        // certain selectors with unsupported type encodings.
        NSMethodSignature *signature = 0;
        @try {
            signature = [klass instanceMethodSignatureForSelector: [method selector]];
        } @catch (NSException *exception) {
            // NSLog(@"instanceMethodSignatureForSelector fail on %@", selectorName);
        }

        // Replace interior ":"s with "_".
        NSString *concatName = [selectorName stringByReplacingOccurrencesOfString:@":" withString:@"_"];
        if ([concatName hasSuffix:@"_"])
            concatName = [concatName substringToIndex:[concatName length] - 1];

        Method met;
        met.name = QString::fromNSString(concatName).toLatin1();

        // Get the return type
        const char *ret = [signature methodReturnType];

        NSString *qtType = mapTypeName([NSString stringWithFormat: @"%s", ret]);
        if (qtType == nil) {
            if (debug())
                NSLog(@"skip method %@ Unknwown return type: %s", selectorName, ret);
            continue;
        }
        met.returnType = QString::fromNSString(qtType).toLatin1();

        // Get arguemnt types
        QList<QByteArray> types;
        bool skip = false;
        for (int i= 2; i < [signature numberOfArguments]; ++i) {
              const char *arg = [signature getArgumentTypeAtIndex : i];
              NSString *qtType = mapTypeName([NSString stringWithFormat: @"%s", arg]);
              if (qtType == nil) {
                  if (debug())
                    NSLog(@"skip method %@ Unknwown argument type: %s", selectorName, arg);
                  skip = true;
                  break;
              }
              types.append(QString::fromNSString(qtType).toLatin1());
        }
        if (skip)
            continue;
        met.argumentTypes = types;

        _methods.append(met);
    }

    return _methods;
}

QList<Property> synthesizeProperties(QList<Method> &methods)
{
    // Accumulate properties using a hash to match getters and setters.
    QHash<QByteArray, Property> _properties;

    // Check for getters: "(T)foo()" or "(bool)isFoo()"
    foreach (Method method, methods) {
        // Skip methods with arguments
        if (method.argumentTypes.count() != 0)
            continue;
        // Skip methods returning void
        if (method.returnType == QByteArray("void"))
            continue;
        // There is a tradeoff between having many properties and exposing
        // potentally destructive functions. Skip some obvious non-getters:
        if (method.name == "retain" || method.name == "autorlease")
            continue;

        QByteArray baseName = method.name;
        // Special case bool properties: "isFoo"
        if (baseName.startsWith("is")) {
            // remove "is" and lower first letter in name
            baseName = baseName.mid(2);
            QByteArray first = baseName.left(1);
            baseName = baseName.mid(1);
            baseName.prepend(first.toLower());
        }

        //
        Property property;
        property.name = baseName;
        property.type = method.returnType;
        property.readOnly = true; // read only until we possibly find a setter bellow.
        _properties.insert(baseName, property);

        // qDebug() << "getter method.name" << baseName << "type" << property.type;
    }

    // Check for setters: "setFoo" with one argument.
    foreach (Method method, methods) {
        if (method.name.startsWith("set") && method.argumentTypes.count() == 1) {
            // remove "set" and lower first letter in name
            QByteArray baseName = method.name;
            baseName = baseName.mid(3);
            QByteArray first = baseName.left(1);
            baseName = baseName.mid(1);
            baseName.prepend(first.toLower());

            if (!_properties.contains(baseName)) {
                if (debug())
                    qDebug() << "skip setter-only property" << baseName;
                // No write-only properties.s
                continue;
            }

            if (_properties[baseName].type != method.argumentTypes.at(0)) {
                if (debug()) {
                    qDebug() << "property getter/setter type mismatch"
                             <<  baseName << _properties[baseName].type
                             << method.argumentTypes.at(0);
                }
                continue;
            }

            // There was a getter; now there is a setter. Mark the property as read/write.
            _properties[baseName].readOnly = false;
        }

        // Special case for "initWith methods". Make them write-ony properties.
        if (method.name.startsWith("initWith") && method.argumentTypes.count() == 1) {
            Property property;
            property.name = method.name;
            // Special special case for "initWithUrl": the argument type must be a url!
            // (the stanard type name decoding will leave it as NSObject/QObject)
            if (method.name == QByteArray("initWithURL")) {
                property.type = "QUrl";
            } else {
                property.type = method.argumentTypes.at(0);
            }
            _properties.insert(method.name, property);
            continue;
        }

    }

    QList<Property> properties;
    properties.reserve(_properties.count());
    foreach (const QByteArray &name, _properties.keys()) {
        properties.append(_properties.value(name));
    }
    return properties;
}

void classPropertiesAndMethods(const QByteArray &className, QList<Property> *properties, QList<Method> *methods)
{
    *methods = classMethods(className);
    *properties = mergeProperties(classProperties(className), synthesizeProperties(*methods));
}

void *allocInit(const QByteArray& className)
{
    const char *name = className.constData();
    NSObject *object = [[NSClassFromString([NSString stringWithUTF8String:name]) alloc] init];
    return object;
}

void *free(void *object)
{
    NSObject *nsobject = (NSObject*)object;
    [nsobject release];
}

// Gets a property (including synthesized properties).
QVariant readProperty(void *object, const QByteArray name)
{
    NSObject *nsobject = (NSObject*)object;
    NSString *key = [NSString stringWithUTF8String:name];
    id value = [object valueForKey:key];
    QVariant variant = convertValue(value);
    return variant;
}

void writeProperty(void *object, const QByteArray name, const QVariant &value)
{
//    qDebug() << "writeProperty" << name << value;

    NSObject *nsobject = (NSObject*)object;
    NSString *key = [NSString stringWithUTF8String:name];
    id objcValue = convertValue(value);
    if (objcValue == nil)
        return;

    // Set the property. Try setValueForkey and then performSelector.
    @try {
        [nsobject setValue:objcValue forKey:key];
    } @catch (NSException *setValueForkeyException) {
        @try {
            SEL selector = NSSelectorFromString(QString(name + ":").toNSString());
            [nsobject performSelector:selector withObject:objcValue];
        } @catch (NSException *performSelectorException) {
            qDebug() << "setValueForKey and performSelector fail for" << name;
            qDebug() << "setValueForKey fail reason" << QString::fromNSString([setValueForkeyException reason]);
            qDebug() << "performSelector fail reason" << QString::fromNSString([performSelectorException reason]);
        }
    }
}

} //namespace
