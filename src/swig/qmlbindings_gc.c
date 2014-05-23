
#include "runtime.h"
#include "cgocall.h"

#ifdef _64BIT
#define SWIG_PARM_SIZE 8
#else
#define SWIG_PARM_SIZE 4
#endif

#pragma dynimport _wrap_qtCreateQmlBindings _wrap_qtCreateQmlBindings ""
#pragma cgo_import_static _wrap_qtCreateQmlBindings
extern void (*_wrap_qtCreateQmlBindings)(void*);
static void (*x_wrap_qtCreateQmlBindings)(void*) = _wrap_qtCreateQmlBindings;

void
·_swig_wrap_qtCreateQmlBindings(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + SWIG_PARM_SIZE + SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtCreateQmlBindings, &p);
}



#pragma dynimport _wrap_qtDestroyQmlBindings _wrap_qtDestroyQmlBindings ""
#pragma cgo_import_static _wrap_qtDestroyQmlBindings
extern void (*_wrap_qtDestroyQmlBindings)(void*);
static void (*x_wrap_qtDestroyQmlBindings)(void*) = _wrap_qtDestroyQmlBindings;

void
·_swig_wrap_qtDestroyQmlBindings(struct {
  uint8 x[SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtDestroyQmlBindings, &p);
}



#pragma dynimport _wrap_qtSetBindingsObjectIdentityType _wrap_qtSetBindingsObjectIdentityType ""
#pragma cgo_import_static _wrap_qtSetBindingsObjectIdentityType
extern void (*_wrap_qtSetBindingsObjectIdentityType)(void*);
static void (*x_wrap_qtSetBindingsObjectIdentityType)(void*) = _wrap_qtSetBindingsObjectIdentityType;

void
·_swig_wrap_qtSetBindingsObjectIdentityType(struct {
  uint8 x[SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE)];
} p)

{
  runtime·cgocall(x_wrap_qtSetBindingsObjectIdentityType, &p);
}



#pragma dynimport _wrap_qtSetBindingsUri _wrap_qtSetBindingsUri ""
#pragma cgo_import_static _wrap_qtSetBindingsUri
extern void (*_wrap_qtSetBindingsUri)(void*);
static void (*x_wrap_qtSetBindingsUri)(void*) = _wrap_qtSetBindingsUri;

void
·_swig_wrap_qtSetBindingsUri(struct {
  uint8 x[SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE)];
} p)

{
  runtime·cgocall(x_wrap_qtSetBindingsUri, &p);
}



#pragma dynimport _wrap_qtSetBindingsVersion _wrap_qtSetBindingsVersion ""
#pragma cgo_import_static _wrap_qtSetBindingsVersion
extern void (*_wrap_qtSetBindingsVersion)(void*);
static void (*x_wrap_qtSetBindingsVersion)(void*) = _wrap_qtSetBindingsVersion;

void
·_swig_wrap_qtSetBindingsVersion(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtSetBindingsVersion, &p);
}



#pragma dynimport _wrap_qtCreateClass _wrap_qtCreateClass ""
#pragma cgo_import_static _wrap_qtCreateClass
extern void (*_wrap_qtCreateClass)(void*);
static void (*x_wrap_qtCreateClass)(void*) = _wrap_qtCreateClass;

void
·_swig_wrap_qtCreateClass(struct {
  uint8 x[SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE) + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtCreateClass, &p);
}



#pragma dynimport _wrap_qtFinalizeClass _wrap_qtFinalizeClass ""
#pragma cgo_import_static _wrap_qtFinalizeClass
extern void (*_wrap_qtFinalizeClass)(void*);
static void (*x_wrap_qtFinalizeClass)(void*) = _wrap_qtFinalizeClass;

void
·_swig_wrap_qtFinalizeClass(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtFinalizeClass, &p);
}



#pragma dynimport _wrap_qtCreateProperty _wrap_qtCreateProperty ""
#pragma cgo_import_static _wrap_qtCreateProperty
extern void (*_wrap_qtCreateProperty)(void*);
static void (*x_wrap_qtCreateProperty)(void*) = _wrap_qtCreateProperty;

void
·_swig_wrap_qtCreateProperty(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE) + (2 * SWIG_PARM_SIZE)];
} p)

{
  runtime·cgocall(x_wrap_qtCreateProperty, &p);
}



#pragma dynimport _wrap_QtQObjectCompanion _wrap_QtQObjectCompanion ""
#pragma cgo_import_static _wrap_QtQObjectCompanion
extern void (*_wrap_QtQObjectCompanion)(void*);
static void (*x_wrap_QtQObjectCompanion)(void*) = _wrap_QtQObjectCompanion;

void
·_swig_getQtQObjectCompanion(struct {
  uint8 x[SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_QtQObjectCompanion, &p);
}



#pragma dynimport _wrap_QuickPaintedItemCompanion _wrap_QuickPaintedItemCompanion ""
#pragma cgo_import_static _wrap_QuickPaintedItemCompanion
extern void (*_wrap_QuickPaintedItemCompanion)(void*);
static void (*x_wrap_QuickPaintedItemCompanion)(void*) = _wrap_QuickPaintedItemCompanion;

void
·_swig_getQuickPaintedItemCompanion(struct {
  uint8 x[SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_QuickPaintedItemCompanion, &p);
}



#pragma dynimport _wrap_QtForeginWindowCompanion _wrap_QtForeginWindowCompanion ""
#pragma cgo_import_static _wrap_QtForeginWindowCompanion
extern void (*_wrap_QtForeginWindowCompanion)(void*);
static void (*x_wrap_QtForeginWindowCompanion)(void*) = _wrap_QtForeginWindowCompanion;

void
·_swig_getQtForeginWindowCompanion(struct {
  uint8 x[SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_QtForeginWindowCompanion, &p);
}



#pragma dynimport _wrap_qtSetClassCompanionType _wrap_qtSetClassCompanionType ""
#pragma cgo_import_static _wrap_qtSetClassCompanionType
extern void (*_wrap_qtSetClassCompanionType)(void*);
static void (*x_wrap_qtSetClassCompanionType)(void*) = _wrap_qtSetClassCompanionType;

void
·_swig_wrap_qtSetClassCompanionType(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtSetClassCompanionType, &p);
}



#pragma dynimport _wrap_qtCreateObject _wrap_qtCreateObject ""
#pragma cgo_import_static _wrap_qtCreateObject
extern void (*_wrap_qtCreateObject)(void*);
static void (*x_wrap_qtCreateObject)(void*) = _wrap_qtCreateObject;

void
·_swig_wrap_qtCreateObject(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtCreateObject, &p);
}



#pragma dynimport _wrap_qtDestroyObject _wrap_qtDestroyObject ""
#pragma cgo_import_static _wrap_qtDestroyObject
extern void (*_wrap_qtDestroyObject)(void*);
static void (*x_wrap_qtDestroyObject)(void*) = _wrap_qtDestroyObject;

void
·_swig_wrap_qtDestroyObject(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtDestroyObject, &p);
}



#pragma dynimport _wrap_qtWriteProperty _wrap_qtWriteProperty ""
#pragma cgo_import_static _wrap_qtWriteProperty
extern void (*_wrap_qtWriteProperty)(void*);
static void (*x_wrap_qtWriteProperty)(void*) = _wrap_qtWriteProperty;

void
·_swig_wrap_qtWriteProperty(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE) + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtWriteProperty, &p);
}



#pragma dynimport _wrap_qtReadProperty _wrap_qtReadProperty ""
#pragma cgo_import_static _wrap_qtReadProperty
extern void (*_wrap_qtReadProperty)(void*);
static void (*x_wrap_qtReadProperty)(void*) = _wrap_qtReadProperty;

void
·_swig_wrap_qtReadProperty(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE) + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtReadProperty, &p);
}



#pragma dynimport _wrap_qtPropertyChanged _wrap_qtPropertyChanged ""
#pragma cgo_import_static _wrap_qtPropertyChanged
extern void (*_wrap_qtPropertyChanged)(void*);
static void (*x_wrap_qtPropertyChanged)(void*) = _wrap_qtPropertyChanged;

void
·_swig_wrap_qtPropertyChanged(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE)];
} p)

{
  runtime·cgocall(x_wrap_qtPropertyChanged, &p);
}



#pragma dynimport _wrap_qtMain _wrap_qtMain ""
#pragma cgo_import_static _wrap_qtMain
extern void (*_wrap_qtMain)(void*);
static void (*x_wrap_qtMain)(void*) = _wrap_qtMain;

void
·QtMain(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE) + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtMain, &p);
}



#pragma dynimport _wrap_qtMainSimple _wrap_qtMainSimple ""
#pragma cgo_import_static _wrap_qtMainSimple
extern void (*_wrap_qtMainSimple)(void*);
static void (*x_wrap_qtMainSimple)(void*) = _wrap_qtMainSimple;

void
·QtMainSimple(struct {
  uint8 x[(2 * SWIG_PARM_SIZE) + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtMainSimple, &p);
}



#pragma dynimport _wrap_qtValueType _wrap_qtValueType ""
#pragma cgo_import_static _wrap_qtValueType
extern void (*_wrap_qtValueType)(void*);
static void (*x_wrap_qtValueType)(void*) = _wrap_qtValueType;

void
·_swig_wrap_qtValueType(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtValueType, &p);
}



#pragma dynimport _wrap_qtValueTypeName _wrap_qtValueTypeName ""
#pragma cgo_import_static _wrap_qtValueTypeName
extern void (*_wrap_qtValueTypeName)(void*);
static void (*x_wrap_qtValueTypeName)(void*) = _wrap_qtValueTypeName;

void
·QtValueTypeName(struct {
  uint8 x[SWIG_PARM_SIZE + (2 * SWIG_PARM_SIZE)];
} p)

{
  runtime·cgocall(x_wrap_qtValueTypeName, &p);
}



#pragma dynimport _wrap_qtValueCopy _wrap_qtValueCopy ""
#pragma cgo_import_static _wrap_qtValueCopy
extern void (*_wrap_qtValueCopy)(void*);
static void (*x_wrap_qtValueCopy)(void*) = _wrap_qtValueCopy;

void
·_swig_wrap_qtValueCopy(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtValueCopy, &p);
}



#pragma dynimport _wrap_qtValueFree _wrap_qtValueFree ""
#pragma cgo_import_static _wrap_qtValueFree
extern void (*_wrap_qtValueFree)(void*);
static void (*x_wrap_qtValueFree)(void*) = _wrap_qtValueFree;

void
·_swig_wrap_qtValueFree(struct {
  uint8 x[SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtValueFree, &p);
}



#pragma dynimport _wrap_qtValueToInt _wrap_qtValueToInt ""
#pragma cgo_import_static _wrap_qtValueToInt
extern void (*_wrap_qtValueToInt)(void*);
static void (*x_wrap_qtValueToInt)(void*) = _wrap_qtValueToInt;

void
·_swig_wrap_qtValueToInt(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtValueToInt, &p);
}



#pragma dynimport _wrap_qtValueFromInt _wrap_qtValueFromInt ""
#pragma cgo_import_static _wrap_qtValueFromInt
extern void (*_wrap_qtValueFromInt)(void*);
static void (*x_wrap_qtValueFromInt)(void*) = _wrap_qtValueFromInt;

void
·_swig_wrap_qtValueFromInt(struct {
  uint8 x[SWIG_PARM_SIZE + SWIG_PARM_SIZE];
} p)

{
  runtime·cgocall(x_wrap_qtValueFromInt, &p);
}



