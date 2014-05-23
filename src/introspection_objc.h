#include <QtCore/QtCore>

#include "forwardingmetaobject.h"


//
namespace ObjCIntrospection
{
    //
    // Class Intropection
    //

    // Get class names.
    QList<QByteArray> nsobjectClassNames();
    QList<QByteArray> nsviewClassNames();
    bool isNSView(const QByteArray className);

    // A property has a name and a type.
    struct Property
    {
        QByteArray type;
        QByteArray name;
        bool readOnly;
    };

    // A Method has a name, return type and a list of argument types.
    struct Method
    {
        QByteArray name;
        QByteArray returnType;
        QList<QByteArray> argumentTypes;
    };

    void classPropertiesAndMethods(const QByteArray &className, QList<Property> *properties,
                                                                QList<Method> *methods);

    // Get all declared properties ("@property")
    QList<Property> classProperties(const QByteArray className);
    // Get all class methods
    QList<Method> classMethods(const QByteArray className);
    // Modern objective-c API declares explicit properties, legacy API may not.
    // This function generates properties from getter/setter methods.
    QList<Property> synthesizeProperties(QList<Method> &methods);
    // Merge two property lists, discarding duplicates.
    QList<Property> mergeProperties(const QList<Property> &a, const QList<Property> &b);

    //
    // Object interaction
    //

    // Allocate and initialize an object
    void *allocInit(const QByteArray& className);
    // Free an object.
    void *free(void *object);
    // Sets a property value (including synthesized properties).
    void writeProperty(void *object, const QByteArray name, const QVariant &value);
    // Gets a property value (including synthesized properties).
    QVariant readProperty(void *object, const QByteArray name);
}

