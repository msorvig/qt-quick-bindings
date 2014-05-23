/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.0
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

// source: qmlbindings.i

package qmlbindings

import "unsafe"
import _ "runtime/cgo"


type _ unsafe.Pointer



type _swig_fnptr *byte
type _swig_memberptr *byte

func _swig_wrap_qtCreateQmlBindings(*_swig_fnptr, *_swig_fnptr, *_swig_fnptr, *_swig_fnptr) SwigcptrStruct_SS_QtQmlBindings_t

func QtCreateQmlBindings(arg1 *_swig_fnptr, arg2 *_swig_fnptr, arg3 *_swig_fnptr, arg4 *_swig_fnptr) Struct_SS_QtQmlBindings_t {
	return _swig_wrap_qtCreateQmlBindings(arg1, arg2, arg3, arg4)
}

func _swig_wrap_qtDestroyQmlBindings(uintptr)

func QtDestroyQmlBindings(arg1 Struct_SS_QtQmlBindings_t) {
	_swig_wrap_qtDestroyQmlBindings(arg1.Swigcptr())
}

func _swig_wrap_qtSetBindingsObjectIdentityType(uintptr, string)

func QtSetBindingsObjectIdentityType(arg1 Struct_SS_QtQmlBindings_t, arg2 string) {
	_swig_wrap_qtSetBindingsObjectIdentityType(arg1.Swigcptr(), arg2)
}

func _swig_wrap_qtSetBindingsUri(uintptr, string)

func QtSetBindingsUri(arg1 Struct_SS_QtQmlBindings_t, arg2 string) {
	_swig_wrap_qtSetBindingsUri(arg1.Swigcptr(), arg2)
}

func _swig_wrap_qtSetBindingsVersion(uintptr, int, int)

func QtSetBindingsVersion(arg1 Struct_SS_QtQmlBindings_t, arg2 int, arg3 int) {
	_swig_wrap_qtSetBindingsVersion(arg1.Swigcptr(), arg2, arg3)
}

func _swig_wrap_qtCreateClass(uintptr, string) SwigcptrStruct_SS_QtClass_t

func QtCreateClass(arg1 Struct_SS_QtQmlBindings_t, arg2 string) Struct_SS_QtClass_t {
	return _swig_wrap_qtCreateClass(arg1.Swigcptr(), arg2)
}

func _swig_wrap_qtFinalizeClass(uintptr, uintptr)

func QtFinalizeClass(arg1 Struct_SS_QtQmlBindings_t, arg2 Struct_SS_QtClass_t) {
	_swig_wrap_qtFinalizeClass(arg1.Swigcptr(), arg2.Swigcptr())
}

func _swig_wrap_qtCreateProperty(uintptr, uintptr, string, string)

func QtCreateProperty(arg1 Struct_SS_QtQmlBindings_t, arg2 Struct_SS_QtClass_t, arg3 string, arg4 string) {
	_swig_wrap_qtCreateProperty(arg1.Swigcptr(), arg2.Swigcptr(), arg3, arg4)
}

type QtClassCompanionType int
func _swig_getQtQObjectCompanion() int
var QtQObjectCompanion int = _swig_getQtQObjectCompanion()
func _swig_getQuickPaintedItemCompanion() int
var QuickPaintedItemCompanion int = _swig_getQuickPaintedItemCompanion()
func _swig_getQtForeginWindowCompanion() int
var QtForeginWindowCompanion int = _swig_getQtForeginWindowCompanion()
func _swig_wrap_qtSetClassCompanionType(uintptr, uintptr, QtClassCompanionType)

func QtSetClassCompanionType(arg1 Struct_SS_QtQmlBindings_t, arg2 Struct_SS_QtClass_t, arg3 QtClassCompanionType) {
	_swig_wrap_qtSetClassCompanionType(arg1.Swigcptr(), arg2.Swigcptr(), arg3)
}

func _swig_wrap_qtCreateObject(uintptr, uintptr) uintptr

func QtCreateObject(arg1 Struct_SS_QtQmlBindings_t, arg2 Struct_SS_QtClass_t) uintptr {
	return _swig_wrap_qtCreateObject(arg1.Swigcptr(), arg2.Swigcptr())
}

func _swig_wrap_qtDestroyObject(uintptr, uintptr)

func QtDestroyObject(arg1 Struct_SS_QtQmlBindings_t, arg2 uintptr) {
	_swig_wrap_qtDestroyObject(arg1.Swigcptr(), arg2)
}

func _swig_wrap_qtWriteProperty(uintptr, uintptr, string, uintptr)

func QtWriteProperty(arg1 Struct_SS_QtQmlBindings_t, arg2 uintptr, arg3 string, arg4 Struct_SS_QtValue_t) {
	_swig_wrap_qtWriteProperty(arg1.Swigcptr(), arg2, arg3, arg4.Swigcptr())
}

func _swig_wrap_qtReadProperty(uintptr, uintptr, string) SwigcptrStruct_SS_QtValue_t

func QtReadProperty(arg1 Struct_SS_QtQmlBindings_t, arg2 uintptr, arg3 string) Struct_SS_QtValue_t {
	return _swig_wrap_qtReadProperty(arg1.Swigcptr(), arg2, arg3)
}

func _swig_wrap_qtPropertyChanged(uintptr, uintptr, string)

func QtPropertyChanged(arg1 Struct_SS_QtQmlBindings_t, arg2 uintptr, arg3 string) {
	_swig_wrap_qtPropertyChanged(arg1.Swigcptr(), arg2, arg3)
}

func QtMain(int, *string, string) int
func QtMainSimple(string) int
func _swig_wrap_qtValueType(uintptr) int

func QtValueType(arg1 Struct_SS_QtValue_t) int {
	return _swig_wrap_qtValueType(arg1.Swigcptr())
}

func QtValueTypeName(int) string
func _swig_wrap_qtValueCopy(uintptr) SwigcptrStruct_SS_QtValue_t

func QtValueCopy(arg1 Struct_SS_QtValue_t) Struct_SS_QtValue_t {
	return _swig_wrap_qtValueCopy(arg1.Swigcptr())
}

func _swig_wrap_qtValueFree(uintptr)

func QtValueFree(arg1 Struct_SS_QtValue_t) {
	_swig_wrap_qtValueFree(arg1.Swigcptr())
}

func _swig_wrap_qtValueToInt(uintptr) int

func QtValueToInt(arg1 Struct_SS_QtValue_t) int {
	return _swig_wrap_qtValueToInt(arg1.Swigcptr())
}

func _swig_wrap_qtValueFromInt(int) SwigcptrStruct_SS_QtValue_t

func QtValueFromInt(arg1 int) Struct_SS_QtValue_t {
	return _swig_wrap_qtValueFromInt(arg1)
}


type SwigcptrStruct_SS_QtQmlBindings_t uintptr
type Struct_SS_QtQmlBindings_t interface {
	Swigcptr() uintptr;
}
func (p SwigcptrStruct_SS_QtQmlBindings_t) Swigcptr() uintptr {
	return uintptr(p)
}

type SwigcptrStruct_SS_QtClass_t uintptr
type Struct_SS_QtClass_t interface {
	Swigcptr() uintptr;
}
func (p SwigcptrStruct_SS_QtClass_t) Swigcptr() uintptr {
	return uintptr(p)
}

type SwigcptrStruct_SS_QtValue_t uintptr
type Struct_SS_QtValue_t interface {
	Swigcptr() uintptr;
}
func (p SwigcptrStruct_SS_QtValue_t) Swigcptr() uintptr {
	return uintptr(p)
}

type SwigcptrVoid uintptr
type Void interface {
	Swigcptr() uintptr;
}
func (p SwigcptrVoid) Swigcptr() uintptr {
	return uintptr(p)
}
