TEMPLATE = lib
TARGET = .dummy/dummy

maven.target = $$PWD/dummy
maven.commands = mvn deploy:deploy-file -Dfile=../lib/QtQuick.jar -DartifactId=QtQuick -Dversion=1.0.0 -DgroupId=local -Dpackaging=jar -Durl=file:../lib/maven
QMAKE_EXTRA_TARGETS +=  maven
PRE_TARGETDEPS = $$maven.target
