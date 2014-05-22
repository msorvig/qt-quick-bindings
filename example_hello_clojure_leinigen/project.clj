(defproject hello "1.0"
  :description "I say Hello to you!"
  :url "http://digia.com"
  :repositories {"local" "file:../lib/maven"}
  :dependencies [[org.clojure/clojure "1.5.1"],
                 [local/QtQuick "1.0.0"]]
  :jvm-opts ["-XstartOnFirstThread", 
             "-Djava.library.path=../lib"]
  :aot [hello.core]
  :main hello.core)
  