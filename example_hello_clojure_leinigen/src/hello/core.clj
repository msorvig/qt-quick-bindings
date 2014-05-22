(ns hello.core)
  (:gen-class :main true)

(defn -main
  "Start Qt Quick"
  [& args]
  (QtQuick/mainSimple "resources/hello.qml"))
