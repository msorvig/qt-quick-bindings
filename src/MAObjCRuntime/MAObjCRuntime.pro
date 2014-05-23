DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

OBJCFLAGS += -std=c99
ANSIFLAG=

# Input
HEADERS += MARTNSObject.h \
           RTIvar.h \
           RTMethod.h \
           RTProperty.h \
           RTProtocol.h \
           RTUnregisteredClass.h

OBJECTIVE_SOURCES += MARTNSObject.mm \
           RTIvar.mm \
           RTMethod.mm \
           RTProperty.mm \
           RTProtocol.mm \
           RTUnregisteredClass.mm

LIBS += -framework Cocoa
           
           





