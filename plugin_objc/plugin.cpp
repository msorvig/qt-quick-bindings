#include <QtCore/QtCore>
#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/qqml.h>

#include "../src/forwardingmetaobject.h"
#include "../src/introspection_objc.h"
#include "../src/qmlbindings.h"

void *createObject(void *context, const char *className)
{
    Q_UNUSED(context)
    return ObjCIntrospection::allocInit(QByteArray(className));
}

void destroyObject(void *context, void *object)
{
    Q_UNUSED(context)
    ObjCIntrospection::free(object);
}

QtValue *readProperty(void *context, void *object, const char *propertyName)
{
    Q_UNUSED(context)
    return qtValueFromVariant(ObjCIntrospection::readProperty(object, QByteArray(propertyName)));
}

void writeProperty(void *context, void *object, const char *propertyName, QtValue *value)
{
    Q_UNUSED(context)
    ObjCIntrospection::writeProperty(object, QByteArray(propertyName), qtValueToVariant(value));
}

void registerObjcClasses(const char *uri)
{
    // Build a QMetaObject for and register each class with QML.
    QList<QByteArray> classNames = ObjCIntrospection::nsobjectClassNames();
    //QList<QByteArray> classNames = ObjCIntrospection::nsviewClassNames();

    QtQmlBindings *qmlBindings = qtCreateQmlBindings(0, createObject, destroyObject,
                                                        readProperty, writeProperty);
    qtSetBindingsObjectIdentityType(qmlBindings, "NSObject *");
    qtSetBindingsUri(qmlBindings, "ObjcBridge");
    qtSetBindingsVersion(qmlBindings, 1, 0);

    qDebug() << "register class count" << classNames.count();

    foreach (QByteArray className, classNames) {
        if (!(className.startsWith("XNSTextView") || className.startsWith(QByteArray("AVPlayer"))
              || className.startsWith("NSSlider")
              ))
            continue;
        qDebug() << "register" << className;

        QtClass *klass = qtCreateClass(qmlBindings, className.constData());

        if (ObjCIntrospection::isNSView(className)) {
            qtSetClassCompanionType(qmlBindings, klass, QtForeginWindowCompanion);
        }

        // Add properties
        QList<ObjCIntrospection::Property> properties;
        QList<ObjCIntrospection::Method> methods;
        ObjCIntrospection::classPropertiesAndMethods(className, &properties, &methods);
        foreach (ObjCIntrospection::Property property, properties) {
            qtCreateProperty(qmlBindings, klass, property.type, property.name);
        }

        qtFinalizeClass(qmlBindings, klass);
    }

    qDebug() << "register done";
}

class QTestObjectPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QTestObjectPlugin")

public:
    void registerTypes(const char *uri)
    {
        registerObjcClasses(uri);
    }
};

#include "plugin.moc"
