DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

OBJCFLAGS += -std=c99
ANSIFLAG=

HEADERS += $$PWD/MARTNSObject.h \
           $$PWD/RTIvar.h \
           $$PWD/RTMethod.h \
           $$PWD/RTProperty.h \
           $$PWD/RTProtocol.h \
           $$PWD/RTUnregisteredClass.h

OBJECTIVE_SOURCES += $$PWD/MARTNSObject.mm \
           $$PWD/RTIvar.mm \
           $$PWD/RTMethod.mm \
           $$PWD/RTProperty.mm \
           $$PWD/RTProtocol.mm \
           $$PWD/RTUnregisteredClass.mm

osx {
    LIBS += -framework AppKit
} 

ios {
    LIBS += -framework UIKit
}
