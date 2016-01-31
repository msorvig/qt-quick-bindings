INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/forwardingmetaobject.h \
    $$PWD/qmlbindings.h \
    $$PWD/qmlbindings_p.h \
    $$PWD/qtwindowcontrolleritem.h \

SOURCES += \
    $$PWD/forwardingmetaobject.cpp \
    $$PWD/qtwindowcontrolleritem.cpp \
    $$PWD/qmlbindings.cpp \
    $$PWD/qtquick.cpp

QT += core-private qml quick
