#ifndef QMLBINDINGS_H
#define QMLBINDINGS_H

#if defined(__cplusplus)
#include <QtCore/qvariant.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif
    
// Bindings instance opaque type
typedef struct QtQmlBindings_t QtQmlBindings;
// QtClass opaque type
typedef struct QtClass_t QtClass;
// QtValue opaque type
typedef struct QtValue_t QtValue;
// QtValuePointer opaque type
typedef struct QtValuePointer_t QtValuePointer;

//
//  Callbacks. Client code implements these.
//

// Called by Qt to create an object
typedef void *(*CreateObjectFn)(const char *className);
// Called by Qt to destroy an object
typedef void (*DestroyObjectFn)(void *object);
// Called by Qt to read a property.
typedef QtValue *(*ReadPropertyFn)(void *object, const char *propertyName);
// typedef void (*ReadPropertyFn)(void *object, const char *propertyName, QtValuePointer *valuePointer);
// Called by Qt to write a property.
typedef void (*WritePropertyFn)(void *object, const char *propertyName, QtValue *value);
//typedef void (*WritePropertyFn)(void *object, const char *propertyName, QtValuePointer *valuePointer);

//
// Class-level API
//

// Initialize QML bindings with pointers to callback functions
QtQmlBindings *qtCreateQmlBindings(CreateObjectFn createObjectFn, DestroyObjectFn destroyObjectFn,
                                   ReadPropertyFn readPropertyFn, WritePropertyFn writePropertyFn);
// Release the Qmlbindings object.
void qtDestroyQmlBindings(QtQmlBindings *bindings);
// Set the object identity type. This type is the "native" type correspoing to
// QObject *, for example NSObject * in the case of Objective-C bindings.
// The bindings will translate between these two types such that that Qt
// sees QObjects and the native side sees this identity type.
void qtSetBindingsObjectIdentityType(QtQmlBindings *bindings, const char *typeName);
// Set the uri and version for which the classes will be registerd for import.
// Defaults to "com.test 1.0" ("import com.test 1.0" from QML)
void qtSetBindingsUri(QtQmlBindings *bindings, const char *uri);
void qtSetBindingsVersion(QtQmlBindings *bindings, int majorVersion, int minorVersion);
// Create a class. Objects of this class can be instantiated as QML items (after qtFinalizeClass
// has been called).
QtClass *qtCreateClass(QtQmlBindings *bindings, const char *className);
// Make a class usable from QML. No properties can be added after qtFinalizeClass has been called.
void qtFinalizeClass(QtQmlBindings *bindings, QtClass *klass);
// Add a property to a class.
void qtCreateProperty(QtQmlBindings *bindings, QtClass *klass,
                      const char *propertyType, const char *propertyName);
// Created objects have a companion Qt object which determines how the
// objects interact with QML and Qt Quick.
typedef enum {
    QtQObjectCompanion,        // Created objects have a companion QObject. The default.
    QuickPaintedItemCompanion, // Created objects have a companion QQUickPaintedItem.
    QtForeginWindowCompanion,  // Created objects have a companion QWindow. Created objects must be native
                               // views which can be safely casted to Wid and passed to QWindow::fromWinId.

} QtClassCompanionType;
void qtSetClassCompanionType(QtQmlBindings *bindings, QtClass *klass, QtClassCompanionType companionType);

//
// Object-level API
//

// Create an object of the given class.
void *qtCreateObject(QtQmlBindings *bindings, QtClass *klass);

// Destroy an object.
void qtDestroyObject(QtQmlBindings *bindings, void *object);
// Write to a property
void qtWriteProperty(QtQmlBindings *bindings, void *object, const char *propertyName, QtValue *value);
// Read from a property
QtValue *qtReadProperty(QtQmlBindings *bindings, void *object, const char *propertyName);
// Signal that a property has changed. Qt will call the ReadPropertyFn callback to read the new value.
void qtPropertyChanged(QtQmlBindings *bindings, void *object, const char *propertyName);


//
// Main
//

extern int qtMain(int argc, char**argv, const char *mainQmlFilePath);
extern int qtMainSimple(const char *mainQmlFilePath);

//
// Type conversion.
//

int qtValueType(QtValue *value); // This is QVariant::type()
const char *qtValueTypeName(int); // This is QMetatype::typeName()
QtValue *qtValueCopy(QtValue *value);
void qtValueFree(QtValue *value);

int qtValueToInt(QtValue *value);
QtValue *qtValueFromInt(int value);


//int qtGetInt(QtValuePointer *);
//void qtSetInt(QtValuePointer *, int value);

#if defined(__cplusplus)
} // extern "C"
#endif
//
// C++ Type conversion. Bindings that can compile C++ can access QVariant directly.
//

#if defined(__cplusplus)
QVariant qtValueToVariant(QtValue *value);
QtValue *qtValueFromVariant(const QVariant &variant);

void qtCreateQObject(QtQmlBindings *bindings, QtClass *klass, QObject **qobject, void **object);

#endif

#endif // QMLBINDINGS_H
