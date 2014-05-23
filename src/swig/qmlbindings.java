/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class qmlbindings {
  public static SWIGTYPE_p_QtQmlBindings_t qtCreateQmlBindings(SWIGTYPE_p_f_p_q_const__char__p_void createObjectFn, SWIGTYPE_p_f_p_void__void destroyObjectFn, SWIGTYPE_p_f_p_void_p_q_const__char__p_QtValue_t readPropertyFn, SWIGTYPE_p_f_p_void_p_q_const__char_p_struct_QtValue_t__void writePropertyFn) {
    long cPtr = qmlbindingsJNI.qtCreateQmlBindings(SWIGTYPE_p_f_p_q_const__char__p_void.getCPtr(createObjectFn), SWIGTYPE_p_f_p_void__void.getCPtr(destroyObjectFn), SWIGTYPE_p_f_p_void_p_q_const__char__p_QtValue_t.getCPtr(readPropertyFn), SWIGTYPE_p_f_p_void_p_q_const__char_p_struct_QtValue_t__void.getCPtr(writePropertyFn));
    return (cPtr == 0) ? null : new SWIGTYPE_p_QtQmlBindings_t(cPtr, false);
  }

  public static void qtDestroyQmlBindings(SWIGTYPE_p_QtQmlBindings_t bindings) {
    qmlbindingsJNI.qtDestroyQmlBindings(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings));
  }

  public static void qtSetBindingsObjectIdentityType(SWIGTYPE_p_QtQmlBindings_t bindings, String typeName) {
    qmlbindingsJNI.qtSetBindingsObjectIdentityType(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), typeName);
  }

  public static void qtSetBindingsUri(SWIGTYPE_p_QtQmlBindings_t bindings, String uri) {
    qmlbindingsJNI.qtSetBindingsUri(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), uri);
  }

  public static void qtSetBindingsVersion(SWIGTYPE_p_QtQmlBindings_t bindings, int majorVersion, int minorVersion) {
    qmlbindingsJNI.qtSetBindingsVersion(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), majorVersion, minorVersion);
  }

  public static SWIGTYPE_p_QtClass_t qtCreateClass(SWIGTYPE_p_QtQmlBindings_t bindings, String className) {
    long cPtr = qmlbindingsJNI.qtCreateClass(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), className);
    return (cPtr == 0) ? null : new SWIGTYPE_p_QtClass_t(cPtr, false);
  }

  public static void qtFinalizeClass(SWIGTYPE_p_QtQmlBindings_t bindings, SWIGTYPE_p_QtClass_t klass) {
    qmlbindingsJNI.qtFinalizeClass(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), SWIGTYPE_p_QtClass_t.getCPtr(klass));
  }

  public static void qtCreateProperty(SWIGTYPE_p_QtQmlBindings_t bindings, SWIGTYPE_p_QtClass_t klass, String propertyType, String propertyName) {
    qmlbindingsJNI.qtCreateProperty(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), SWIGTYPE_p_QtClass_t.getCPtr(klass), propertyType, propertyName);
  }

  public static void qtSetClassCompanionType(SWIGTYPE_p_QtQmlBindings_t bindings, SWIGTYPE_p_QtClass_t klass, QtClassCompanionType companionType) {
    qmlbindingsJNI.qtSetClassCompanionType(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), SWIGTYPE_p_QtClass_t.getCPtr(klass), companionType.swigValue());
  }

  public static SWIGTYPE_p_void qtCreateObject(SWIGTYPE_p_QtQmlBindings_t bindings, SWIGTYPE_p_QtClass_t klass) {
    long cPtr = qmlbindingsJNI.qtCreateObject(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), SWIGTYPE_p_QtClass_t.getCPtr(klass));
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public static void qtDestroyObject(SWIGTYPE_p_QtQmlBindings_t bindings, SWIGTYPE_p_void object) {
    qmlbindingsJNI.qtDestroyObject(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), SWIGTYPE_p_void.getCPtr(object));
  }

  public static void qtWriteProperty(SWIGTYPE_p_QtQmlBindings_t bindings, SWIGTYPE_p_void object, String propertyName, SWIGTYPE_p_QtValue_t value) {
    qmlbindingsJNI.qtWriteProperty(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), SWIGTYPE_p_void.getCPtr(object), propertyName, SWIGTYPE_p_QtValue_t.getCPtr(value));
  }

  public static SWIGTYPE_p_QtValue_t qtReadProperty(SWIGTYPE_p_QtQmlBindings_t bindings, SWIGTYPE_p_void object, String propertyName) {
    long cPtr = qmlbindingsJNI.qtReadProperty(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), SWIGTYPE_p_void.getCPtr(object), propertyName);
    return (cPtr == 0) ? null : new SWIGTYPE_p_QtValue_t(cPtr, false);
  }

  public static void qtPropertyChanged(SWIGTYPE_p_QtQmlBindings_t bindings, SWIGTYPE_p_void object, String propertyName) {
    qmlbindingsJNI.qtPropertyChanged(SWIGTYPE_p_QtQmlBindings_t.getCPtr(bindings), SWIGTYPE_p_void.getCPtr(object), propertyName);
  }

  public static int qtMain(int argc, String[] argv, String mainQmlFilePath) {
    return qmlbindingsJNI.qtMain(argc, argv, mainQmlFilePath);
  }

  public static int qtMainSimple(String mainQmlFilePath) {
    return qmlbindingsJNI.qtMainSimple(mainQmlFilePath);
  }

  public static int qtValueType(SWIGTYPE_p_QtValue_t value) {
    return qmlbindingsJNI.qtValueType(SWIGTYPE_p_QtValue_t.getCPtr(value));
  }

  public static String qtValueTypeName(int arg0) {
    return qmlbindingsJNI.qtValueTypeName(arg0);
  }

  public static SWIGTYPE_p_QtValue_t qtValueCopy(SWIGTYPE_p_QtValue_t value) {
    long cPtr = qmlbindingsJNI.qtValueCopy(SWIGTYPE_p_QtValue_t.getCPtr(value));
    return (cPtr == 0) ? null : new SWIGTYPE_p_QtValue_t(cPtr, false);
  }

  public static void qtValueFree(SWIGTYPE_p_QtValue_t value) {
    qmlbindingsJNI.qtValueFree(SWIGTYPE_p_QtValue_t.getCPtr(value));
  }

  public static int qtValueToInt(SWIGTYPE_p_QtValue_t value) {
    return qmlbindingsJNI.qtValueToInt(SWIGTYPE_p_QtValue_t.getCPtr(value));
  }

  public static SWIGTYPE_p_QtValue_t qtValueFromInt(int value) {
    long cPtr = qmlbindingsJNI.qtValueFromInt(value);
    return (cPtr == 0) ? null : new SWIGTYPE_p_QtValue_t(cPtr, false);
  }

}