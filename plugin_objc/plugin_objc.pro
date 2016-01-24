TARGET  = qmlobjcbridgeplugin
TARGETPATH = ObjcBridge
IMPORT_VERSION = 1.0

TEMPLATE = lib
QT += qml quick
QT += core-private

OBJECTS_DIR = .obj
MOC_DIR = .moc

HEADERS += ../src/forwardingmetaobject.h
SOURCES += ../src/forwardingmetaobject.cpp

HEADERS += ../src/qtwindowcontrolleritem.h
SOURCES += ../src/qtwindowcontrolleritem.cpp

HEADERS += ../src/qmlbindings.h
HEADERS += ../src/qmlbindings_p.h
SOURCES += ../src/qmlbindings.cpp

include (../src/MAObjCRuntime/MAObjCRuntime.pri)

HEADERS += ../src/introspection_objc.h
OBJECTIVE_SOURCES += ../src/introspection_objc.mm

SOURCES += plugin.cpp

DEFINES += QT_BINDINGS_HAS_QVARIANT

osx {
    # link against frameworks to register their views
    LIBS +=  -framework ApplicationServices -framework WebKit -framework MapKit -framework AVKit
}

load(qml_plugin)
