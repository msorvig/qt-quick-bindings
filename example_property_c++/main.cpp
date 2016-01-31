#include <qtquick.h>


// A C++ business logic class
class Foo
{
public:
    // Standard C++ class inteface
    Foo() {}
    void set_bar(int value);
    int bar() const;
    
private:
    // Standard member storage
    int m_bar;

public:
    // Declare type with properties and invokables as interface to Qt
    static qt::type qt_foo;
    static qt::property<int> qt_bar;
    static qt::invokable qt_clear; // A Qt-only API with no corresponding C++ function
};

// Definitions
void Foo::set_bar(int value)
{
    m_bar = value;
    qt_bar.notify_changed(this); // send change notificaton to Qt
}

int Foo::bar() const
{
    return m_bar;
}

// Type with type name
qt::type Foo::qt_foo("Foo");
// Property with property name and read/write callbacks using the C++ class API
qt::property<int> Foo::qt_bar(&Foo::qt_foo, "bar", std::mem_fn(&Foo::bar), std::mem_fn(&Foo::set_bar));
// Invokable with callback via lambda
qt::invokable Foo::qt_clear(&Foo::qt_foo, [] (Foo *instance) { instance->set_bar(0); } );


int main(int argc, char **argv)
{
    auto qt_bindings = qt::bindings();

    // Create application instances and register with Qt.
    Foo foo;
    foo.set_bar(8128);
    qt_bindings.registerInstance(&Foo::qt_foo, &foo, "foo");

    return qt::main(argc, argv, "property.qml");
}

