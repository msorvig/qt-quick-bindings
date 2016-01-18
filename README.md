QtQuick Language Bindings
=========================

WARNING: This is a research project with very (very!) incomplete bindings.

This project is a playground for QObject and QML/QtQuick programming language bindings.
At the base is a C API for the Qt meta object system.

* QtDeclarative Patch
A patched for QtDeclarative is required, see 0001-WIP-Support-run-time-QML-type-creation.patch.
The Qt revisions this patch applies to is from Feb 2014:

    QtDeclarative ef4cf6585a61a00e33091277217b6346a1e6e7fd
    QtBase 30fd22b9574def54726e7b193127cc0c901c1b4c

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

* Values and data type conversion

Values are represented using QtValue, which corresponds to QVariant.


* Examples

Examples are prefixed with "example_", and are ordered in increasing complexity

    "example_hello_": Simplest QML hello world.
    "example_hello_model_stringlist": Exporting a string list data model to Qt.

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
