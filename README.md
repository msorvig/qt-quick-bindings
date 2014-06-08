QtQuick Bindings, breadth first.

WARNING: Language support is very (very!) incomplete. Proceed with caution. 
This is probably not the project you are looking for.

This project is a reasearch playground for QObject and QML/QtQuick bindings
to various languages. At the base is a C API for the Qt meta object system.

* Structure
The API and build artifacts have two levels:
    qmlbindings: Low-level bindings API. A direct wrapping of the C API.
    qtquick: High-level user-facing API in the target language
[The structure is not fully realized yet and is subject to change.]

* SWIG
Some qmlbindings are generated with SWIG. The bindings are checked into src/swig.
Use src/runswig.sh to regenerate.

* Libraries
Libraries are built by the projects in "qmake_" prefixed directories.

* Examples
Examples are prefixed with "example_". "example_hello_" is the simplest QML hello world

* C bindings
src/qmlbindings.h
qmake_c
example_hello_c

* Java, Scala, Clojure bindings
qmake_java
qmake_java_maven
example_hello_java
example_hello_scala
example_hello_clojure_leinigen

* C# (mono) bindings
qmake_csharp
example_hello_c#

* Objective C bindings
plugin_objc

* Rust bindings
example_hello_rust
