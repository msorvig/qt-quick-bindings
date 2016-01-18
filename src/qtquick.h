#ifndef QTQUICK_H
#define QTQUICK_H

// high-level C++ bindings

namespace qt {
    namespace detail {

        // include low-level C bindings as an implementation detail.
#       include <qmlbindings.h>
        
    } // namespace detail
    
    int main(int argc, char **argv, const char *qml_file_name) {
        return detail::qtMain(argc, argv, qml_file_name);
    }
} // namespace qt

#endif
