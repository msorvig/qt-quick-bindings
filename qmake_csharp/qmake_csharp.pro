TEMPLATE = lib
TARGET = ../lib/qmlbindings_csharp
SOURCES += ../src/swig/qmlbindings_csharp_wrap.c
INCLUDEPATH += $$PWD/../src/ /System/Library/Frameworks/JavaVM.framework/Headers 
LIBS += -L$$PWD/../lib -lqmlbindings

# build the qmlbindings module
module.target = $$PWD/dummy
module.commands = mcs -target:module -out:../lib/qmlbindings.netmodule\
                $$PWD/../src/swig/QtClassCompanionType.cs \
                $$PWD/../src/swig/SWIGTYPE_p_f_p_void_p_q_const__char__p_QtValue_t.cs \
                $$PWD/../src/swig/SWIGTYPE_p_QtClass_t.cs \
                $$PWD/../src/swig/SWIGTYPE_p_f_p_void_p_q_const__char_p_struct_QtValue_t__void.cs \
                $$PWD/../src/swig/SWIGTYPE_p_QtQmlBindings_t.cs \
                $$PWD/../src/swig/SWIGTYPE_p_p_char.cs \
                $$PWD/../src/swig/SWIGTYPE_p_QtValue_t.cs \
                $$PWD/../src/swig/SWIGTYPE_p_void.cs \
                $$PWD/../src/swig/SWIGTYPE_p_f_p_q_const__char__p_void.cs \
                $$PWD/../src/swig/qmlbindings.cs \
                $$PWD/../src/swig/SWIGTYPE_p_f_p_void__void.cs \
                $$PWD/../src/swig/qmlbindingsPINVOKE.cs

QMAKE_EXTRA_TARGETS += module
PRE_TARGETDEPS = $$module.target
