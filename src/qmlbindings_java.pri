SOURCES += $$PWD/swig/qmlbindings_java_wrap.c
INCLUDEPATH += $$PWD /System/Library/Frameworks/JavaVM.framework/Headers 
LIBS += -L$$PWD/../lib -lqmlbindings

# Manual build for -qmlbindings.jar- QtQuick.jar

# Comile classes
qmlbindingsclasses.target = $$PWD/.javaclass/dummy
qmlbindingsclasses.commands = javac -d $$PWD/.javaclass/  \
                    $$PWD/QtQuick.java \
                    $$PWD/swig/qmlbindings.java \
                    $$PWD/swig/qmlbindingsJNI.java \
                    $$PWD/swig/QtClassCompanionType.java \
                    $$PWD/swig/SWIGTYPE_p_QtClass_t.java \
                    $$PWD/swig/SWIGTYPE_p_f_p_q_const__char__p_void.java \
                    $$PWD/swig/SWIGTYPE_p_f_p_void_p_q_const__char_p_struct_QtValue_t__void.java \
                    $$PWD/swig/SWIGTYPE_p_QtQmlBindings_t.java \
                    $$PWD/swig/SWIGTYPE_p_f_p_void__void.java \
                    $$PWD/swig/SWIGTYPE_p_QtValue_t.java \
                    $$PWD/swig/SWIGTYPE_p_f_p_void_p_q_const__char__p_QtValue_t.java \
                    $$PWD/swig/SWIGTYPE_p_void.java

# Create .jar with classes
qmlbindingsjar.target = $$PWD/../lib/qmlbindings.jar
qmlbindingsjar.depends = qmlbindingsclasses
qmlbindingsjar.commands = jar cf $$PWD/../lib/QtQuick.jar \
                   -C $$PWD/.javaclass/ QtQuick.class \
                   -C $$PWD/.javaclass/ qmlbindings.class \
                   -C $$PWD/.javaclass/ qmlbindingsJNI.class \
                   -C $$PWD/.javaclass/ QtClassCompanionType.class \
                   -C $$PWD/.javaclass/ SWIGTYPE_p_QtClass_t.class \
                   -C $$PWD/.javaclass/ SWIGTYPE_p_f_p_q_const__char__p_void.class \
                   -C $$PWD/.javaclass/ SWIGTYPE_p_f_p_void_p_q_const__char_p_struct_QtValue_t__void.class \
                   -C $$PWD/.javaclass/ SWIGTYPE_p_QtQmlBindings_t.class \
                   -C $$PWD/.javaclass/ SWIGTYPE_p_f_p_void__void.class \
                   -C $$PWD/.javaclass/ SWIGTYPE_p_QtValue_t.class \
                   -C $$PWD/.javaclass/ SWIGTYPE_p_f_p_void_p_q_const__char__p_QtValue_t.class \
                   -C $$PWD/.javaclass/ SWIGTYPE_p_void.class

#qtquickclasses.target = $$PWD/.javaclass/dummy
#qtquickclasses.commands = javac -d $$PWD/.javaclass/  \
#                          -cp $$PWD/../lib/qmlbindings.jar \
#                          $$PWD/QtQuick.java

#qtquickjar.target = $$PWD/../lib/QtQuick.jar
#qtquickjar.depends = qtquickclasses
#qtquickjar.commands = jar cf $$PWD/../lib/QtQuick.jar \
#                    -C $$PWD/.javaclass/QtQuick.class \

                    
#QMAKE_EXTRA_TARGETS += qtquickclasses qtquickjar
QMAKE_EXTRA_TARGETS += qmlbindingsclasses qmlbindingsjar
#PRE_TARGETDEPS = $$qtquickjar.target
PRE_TARGETDEPS = $$qmlbindingsjar.target
