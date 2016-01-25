#include "qmlbindings.h"
#include "qmlbindings_p.h"
#include "forwardingmetaobject.h"

#include <QtCore/qvariant.h>
#include <QtCore/qmetaobject.h>

#include <QtGui/qwindow.h>
#include <QtGui/qpainter.h>
#include <QtGui/qguiapplication.h>

#include <QtQml/qqml.h>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>

struct QtClass_t
{
    QtQmlBindings *bindings;
    ForwardMetaObjectBuilder *metaObjectBuilder;
    const QMetaObject *metaObject;
    QtClassCompanionType companionType;
};

class QmlBindingsForwardingObject;
struct QtQmlBindings_t
{
    void *context;
    CreateObjectFn createObjectsFn;
    DestroyObjectFn destroyObjectFn;
    ReadPropertyFn readPropertyFn;
    WritePropertyFn writePropertyFn;
    QByteArray qobjectIdentityType;
    QByteArray uri;
    int majorVersion;
    int minorVersion;

    QHash<QByteArray, QtClass*> classes; // class name -> class
    QHash<void *, QmlBindingsForwardingObject *> objects;
};

struct QtValue_t
{
    QVariant variant;  // QtValue is a QVariant behind the scenes.
};

QVariant qtValueToVariant(QtValue *value);
QtValue *qtValueFromVariant(const QVariant &variant);

void qtWritePropertyFromQt(QtQmlBindings *bindings, void *object, QByteArray name, QVariant value);

QmlBindingsForwardingObject::QmlBindingsForwardingObject(QtClass *_qtClass)
    :bindings(_qtClass->bindings), qtClass(_qtClass), boundObject(0)
{
    setMetaObject(qtClass->metaObject);
    boundObject = qtCreateObject(bindings, qtClass);
 //   bindings->objects.insert(boundObject, this);
}

QVariant QmlBindingsForwardingObject::readProperty(const QByteArray &name)
{
    return qtValueToVariant(qtReadProperty(bindings, boundObject, name.constData()));
}

void QmlBindingsForwardingObject::wrtiteProperty(const QByteArray &name, const QVariant &value)
{
    qtWritePropertyFromQt(bindings, boundObject, name, value);
}

void QmlBindingsForwardingObject::propertyChange(const QByteArray name)
{

}

QmlBindingsForwardingWindowController::QmlBindingsForwardingWindowController(QtClass *_qtClass)
    :bindings(_qtClass->bindings), qtClass(_qtClass), boundObject(0)
{
    setMetaObject(qtClass->metaObject);
    boundObject = qtCreateObject(bindings, qtClass);

    // The created object is a native view which can be cased to Wid.
    QWindow *controlledWindow = QWindow::fromWinId(WId(boundObject));
    QtWindowControllerItem::setWindow(controlledWindow);
}

QVariant QmlBindingsForwardingWindowController::readProperty(const QByteArray &name)
{
    return qtValueToVariant(qtReadProperty(bindings, boundObject, name.constData()));
}

void QmlBindingsForwardingWindowController::wrtiteProperty(const QByteArray &name, const QVariant &value)
{
    qtWritePropertyFromQt(bindings, boundObject, name, value);
}

void QmlBindingsForwardingWindowController::propertyChange(const QByteArray name)
{

}

QmlBindingsPaintedItem::QmlBindingsPaintedItem(QtClass *_qtClass)
    :bindings(_qtClass->bindings), qtClass(_qtClass), boundObject(0)
{
    setMetaObject(qtClass->metaObject);
    boundObject = qtCreateObject(bindings, qtClass);
}

QVariant QmlBindingsPaintedItem::readProperty(const QByteArray &name)
{
    return qtValueToVariant(qtReadProperty(bindings, boundObject, name.constData()));
}

void QmlBindingsPaintedItem::wrtiteProperty(const QByteArray &name, const QVariant &value)
{
    qtWritePropertyFromQt(bindings, boundObject, name, value);
}

void QmlBindingsPaintedItem::propertyChange(const QByteArray name)
{

}

void QmlBindingsPaintedItem::paint(QPainter *painter)
{
    painter->fillRect(contentsBoundingRect(), QBrush(QColor(Qt::red)));
}

QtQmlBindings *qtCreateQmlBindings(void* context,
                                   CreateObjectFn createObjectFn, DestroyObjectFn destroyObjectFn,
                                   ReadPropertyFn readPropertyFn, WritePropertyFn writePropertyFn)
{
    QtQmlBindings *bindings = new QtQmlBindings;

    // Store user context
    bindings->context = context;

    // Store user function pointers.
    bindings->createObjectsFn = createObjectFn;
    bindings->destroyObjectFn = destroyObjectFn;
    bindings->readPropertyFn = readPropertyFn;
    bindings->writePropertyFn = writePropertyFn;

    // Set some sensible(?) defults.
    bindings->uri = "com.test";
    bindings->majorVersion = 1;
    bindings->minorVersion = 0;

    return bindings;
}

void qtDestroyQtClass(QtClass *klass)
{
    delete klass->metaObjectBuilder;
}

void qtDestroyQmlBindings(QtQmlBindings *bindings)
{
    foreach(QtClass *klass, bindings->classes.values())
        qtDestroyQtClass(klass);
    qDeleteAll(bindings->classes);
    delete bindings;
}

void qtSetBindingsObjectIdentityType(QtQmlBindings *bindings, const char *typeName)
{
    bindings->qobjectIdentityType = QByteArray(typeName);
}

void qtSetBindingsUri(QtQmlBindings *bindings, const char *uri)
{
    bindings->uri = uri;
}

void qtSetBindingsVersion(QtQmlBindings *bindings, int majorVersion, int minorVersion)
{
    bindings->majorVersion = majorVersion;
    bindings->minorVersion = minorVersion;
}

QtClass *qtCreateClass(QtQmlBindings *bindings, const char *className)
{
    QByteArray name(className);
    QtClass *klass = new QtClass;

    klass->bindings = bindings;
    klass->metaObjectBuilder = new ForwardMetaObjectBuilder;
    klass->metaObjectBuilder->setClassName(name);
    klass->metaObject = 0;
    klass->companionType = QtQObjectCompanion;

    bindings->classes.insert(name, klass);
    return klass;
}

void qtCreateProperty(QtQmlBindings *bindings, QtClass *klass,
                      const char *propertyType, const char *propertyName)
{
    // Map properties of the native object identity type to QObject.
    QByteArray type = (QByteArray(propertyType) == bindings->qobjectIdentityType) ?
                      QByteArray("QObject *") : QByteArray(propertyType);

    klass->metaObjectBuilder->addProperty(QByteArray(propertyName), type);
}

void qtSetClassCompanionType(QtQmlBindings *bindings, QtClass *klass, QtClassCompanionType companionType)
{
    klass->companionType = companionType;
}

void createQmlBindingsObject(void *memory, void *context)
{
    // Crate a new object. Select class according to companion object type
    QtClass *klass = static_cast<QtClass*>(context);
    if (klass->companionType == QtQObjectCompanion) {
        new (memory) QmlBindingsForwardingObject(klass);
    } else if (klass->companionType == QuickPaintedItemCompanion) {
        new (memory) QmlBindingsPaintedItem(klass);
    } else if (klass->companionType == QtForeginWindowCompanion) {
        new (memory) QmlBindingsForwardingWindowController(klass);
    }
}

void qtFinalizeClass(QtQmlBindings *bindings, QtClass *klass)
{
    if (klass->companionType > QtForeginWindowCompanion) {
        qDebug() << "qtFinalizeClass: Unknown object companion type" << klass->companionType;
        return;
    }

    // Set meta object superclass according to companion object type
    if (klass->companionType == QtQObjectCompanion) {
        klass->metaObjectBuilder->setSuperClass(&QObject::staticMetaObject);
    } else if (klass->companionType == QuickPaintedItemCompanion) {
        klass->metaObjectBuilder->setSuperClass(&QQuickPaintedItem::staticMetaObject);
    } else if (klass->companionType == QtForeginWindowCompanion) {
        klass->metaObjectBuilder->setSuperClass(&QtWindowControllerItem::staticMetaObject);
    }

    // Build meta object.
    klass->metaObject = klass->metaObjectBuilder->metaObject();
/*
    qmlRegisterSingletonType<QmlBindingsForwardingObject>(
        bindings->uri, bindings->majorVersion, bindings->minorVersion,
        klass->metaObject->className(),
*/
    // Register class with QM. Select class C++ type according to companion object type
    if (klass->companionType == QtQObjectCompanion) {
        qmlRegisterCustomMetaObjectType<QmlBindingsForwardingObject>
            (bindings->uri, bindings->majorVersion, bindings->minorVersion,
             klass->metaObject->className(), createQmlBindingsObject, klass, klass->metaObject);
    } else if (klass->companionType == QuickPaintedItemCompanion) {
        qmlRegisterCustomMetaObjectType<QmlBindingsPaintedItem>
            (bindings->uri, bindings->majorVersion, bindings->minorVersion,
             klass->metaObject->className(), createQmlBindingsObject, klass, klass->metaObject);
    } else if (klass->companionType == QtForeginWindowCompanion) {
        qmlRegisterCustomMetaObjectType<QmlBindingsForwardingWindowController>
            (bindings->uri, bindings->majorVersion, bindings->minorVersion,
             klass->metaObject->className(), createQmlBindingsObject, klass, klass->metaObject);
    }
}

void *qtCreateObject(QtQmlBindings *bindings, QtClass *klass)
{
    return bindings->createObjectsFn(bindings->context, klass->metaObject->className());
}

void qtCreateQObject(QtQmlBindings *bindings, QtClass *klass, QObject **qobject, void **object)
{
    QmlBindingsForwardingObject *qobj = new QmlBindingsForwardingObject(klass);
    *qobject = qobj;

    qDebug() << "qtCreateQObject" << qobj << *qobject;
    qDebug() << "metaobject" << qobj->metaObject();

    *object = qobj->boundObject;
}

void qtDestroyObject(QtQmlBindings *bindings, void *object)
{
    bindings->destroyObjectFn(bindings->context, object);
}

QtValue *qtReadProperty(QtQmlBindings *bindings, void *object, const char *propertyName)
{
    return bindings->readPropertyFn(bindings->context, object, propertyName);
}

void qtWritePropertyFromQt(QtQmlBindings *bindings, void *object, QByteArray name, QVariant value)
{
    // The dual object identity setup
    //
    // Objects have two identities; the QObject on the Qt side and
    // the bound object type on the bindings side.
    //
    // Consider the following example: (Objective-C bindings)
    //
    // AVPlayer {
    //    id : thePlayer
    // }
    //
    // AVPlayerView {
    //     player : thePlayer
    // }
    //
    // The "player : thePlayer" assignment will produce a writeProperty
    // call on the AVPlayerView object, assigning the AVPlayer QObject *
    // to the "player" property. This wont work, because AVPlayerView
    // expects an NSObjet.
    //
    // Make this work by assigning the bound object pointer to the property.
    //
    QtValue *_value = 0;
    // Check if the value is a QmlBindingsForwardingObject.
    if (QMetaType::Type(value.type()) == QMetaType::QObjectStar) {
        QObject *object = qvariant_cast<QObject *>(value);
        QmlBindingsForwardingObject *forwardingObject =
            qobject_cast<QmlBindingsForwardingObject *>(object);
        if (forwardingObject) {
            // It is a QmlBindingsForwardingObject: assign the bound object pointer.
            _value = qtValueFromVariant(QVariant::fromValue(forwardingObject->boundObject));
        }
    }

    if (_value == 0)
        _value = qtValueFromVariant(value);

    qtWriteProperty(bindings, object, name.constData(), _value);
    qtValueFree(_value);
}

void qtWriteProperty(QtQmlBindings *bindings, void *object, const char *propertyName, QtValue *value)
{
    return bindings->writePropertyFn(bindings->context, object, propertyName, value);
}

void qtPropertyChanged(QtQmlBindings *bindings, void *object, const char *propertyName)
{
    QmlBindingsForwardingObject *forwardingObject = bindings->objects.value(object);
    if (forwardingObject)
        return;
    //forwardingObject->propertyChanged(propertyName);

    //klass->metaObject->indexOfSignal()
}

int qtMain(int argc, char**argv, const char *mainQmlFilePath)
{
    QGuiApplication app(argc, argv);
    QQuickView quickView;
    QObject::connect(quickView.engine(), SIGNAL(quit()), &quickView, SLOT(close()));
    quickView.setSource(QUrl::fromLocalFile(QString::fromUtf8(mainQmlFilePath)));
    quickView.show();
    return app.exec();
}

int qtMainSimple(const char *mainQmlFilePath)
{
    static int argc = 0;
    static char *argv = "";
    return qtMain(argc, &argv, mainQmlFilePath);
}

int qtValueType(QtValue *value)
{
    return value->variant.type();
}

const char *qtValueTypeName(int valueType)
{
    return QMetaType::typeName(valueType);
}

QtValue *qtValueCopy(QtValue *value)
{
    QtValue *newValue = new QtValue;
    newValue->variant = value->variant;
    return newValue;
}

void qtValueFree(QtValue *value)
{
    delete value;
}

int qtValueToInt(QtValue *value)
{
    return value->variant.toInt();
}

QtValue *qtValueFromInt(int value)
{
    QtValue *newValue = new QtValue;
    newValue->variant = QVariant::fromValue(value);
    return newValue;
}

const char *qtValueString(QtValue *value)
{
    QString str = value->variant.toString();
    static QByteArray utf8Str; // ### reentrancy?
    utf8Str = str.toUtf8();
    return utf8Str.constData();
}

QtValue *qtValueStringFromUtf8(QtValue *value, char *buffer, int bufferLength)
{
    QtValue *newValue = new QtValue;
    newValue->variant = QVariant::fromValue(QString::fromUtf8(buffer, bufferLength));
    return newValue;
}

int qtValueStringCopyToUtf8(QtValue *value, char *buffer, int bufferLength)
{
    // Convert to utf-8 and copy to output buffer, possibly
    // truncating the string if the buffer is too small.
    QByteArray utf8 = value->variant.toString().toUtf8();
    int copyLength = qMin(utf8.length(), bufferLength - 1);
    qstrncpy(buffer, utf8.constData(), copyLength);

    // Terminate with 0 byte, either at string end or output buffer end
    buffer[copyLength] = 0;

    // Return the number of bytes copied.
    return copyLength;
}

/*
int qtValueStringCopyToUtf16(QtValue *value, char *buffer, int bufferLength)
{
    // Convert to utf-16 and copy to output buffer, possibly
    // truncating the string if the buffer is too small.
    QString string = value->variant.toString();
    const ushort *utf16 = string.utf16();
    int copyLength = qMin(, bufferLength - 1);
    qstrncpy(buffer, utf16, copyLength);

    // Terminate with 0 byte, either at string end or output buffer end
    buffer[copyLength] = 0;

    // Return the number of bytes copied.
    return copyLength;
}
*/

int qtValueStringLength(QtValue *value)
{
    QString str = value->variant.toString();
    QByteArray utf8Str = str.toUtf8();
    return utf8Str.length();
}

QVariant qtValueToVariant(QtValue *value)
{
    return value->variant;
}

QtValue *qtValueFromVariant(const QVariant &variant)
{
    QtValue *newValue = new QtValue;
    newValue->variant = variant;
    return newValue;
}

