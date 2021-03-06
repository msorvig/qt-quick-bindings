#ifndef QTQUICK_H
#define QTQUICK_H

#include <functional>
#include <iostream>
#include <map>
#include <vector>

// high-level C++ bindings
class Foo;
namespace qt {
    namespace detail {

        // Include low-level C bindings as an implementation detail.
        // Note that using a "detail" private namespace is not sufficient
        // to insulate against source and binary incompatible changes
        // in the C bindings API -- Users of the C++ public API will
        // still have to be recompiled in that case.
#       include <qmlbindings.h>

        // QtValue type conversion. Build API based on template specialization
        // on top of the C API.
        template <typename T> QtValue *qtvalue_from(const T&& value)  { return 0; } // error case
        template <> QtValue *qtvalue_from<int>(const int&& value) { return qtValueFromInt(value); }

        template <typename T> T qtvalue_to(QtValue* value)  { return T(); } // error case
        template <> int qtvalue_to<int>(QtValue* value)  { return qtValueToInt(value); }

        struct cmp_str { bool operator()(char const *a, char const *b) const { return std::strcmp(a, b) < 0; } };

        class property_base;
    } // namespace detail

    // qt::type exposes a class/type to Qt
    // Usage:
    //    qt::type qt_type("class");
    // where Class is the native class type and "class" is its name
    class type
    {
    public:
        type(const char *typeName)
        {
            m_types[typeName] = this;
        }

    protected:
        detail::QtValue *read_property(const char *property_name, void *instance);
        void write_property(const char *property_name, void *instance, detail::QtValue *value);

        detail::QtClass *m_qt_class;
        std::map<const char *, detail::property_base *, detail::cmp_str> m_properties;

        // global type registry. type name -> type *
        static std::map<const char *, type *, detail::cmp_str> m_types;

        friend class bindings;
        template <typename T>
        friend class property;
    };

    namespace detail {
        // stores a typed reader function and provideds a generic QtValue API for reading.
        template <typename I, typename V>
        class qtvalue_reader
        {
        public:
            template<typename Fn>
            qtvalue_reader(Fn fn) : m_fn(fn) {}

            QtValue *operator()(void *instance)
            {
                return qtvalue_from(m_fn(reinterpret_cast<I>(instance)));
            }
            std::function<V(I)> m_fn;
        };

        // stores a typed writer function and provideds a generic QtValue API for writing.
        template <typename I, typename V>
        class qtvalue_writer
        {
        public:
            template<typename Fn>
            qtvalue_writer(Fn fn) : m_fn(fn) {}

            void operator()(void *instance, QtValue *value)
            {
                m_fn(reinterpret_cast<I>(instance), qtvalue_to<V>(value));
            }
            std::function<void(I, V)> m_fn;
        };

        class property_base
        {
        public:
            property_base() : m_type(0), m_isVriting(false) {}

            const char *property_name()
            {
                return m_property_name;
            }

            const char *type_name()
            {
                return m_type_name;
            }

        protected:
            // Called by Qt to read and write values
            QtValue *read(void *instance)
            {
                return m_reader(instance);
            }
            void write(void *instance, QtValue *value)
            {
                m_isVriting = true;
                m_writer(instance, value);
                m_isVriting = false;
            }

            // Called by the applicaiton to signal property value change.
            void notify_changed(void *instance)
            {
                if (m_isVriting)
                    return; // prevent self-notifications.

                // ### notify
                // m_type->notify_changed(this, instance);
            }

            type *m_type;   // parent type
            const char *m_property_name;
            const char *m_type_name;
            std::function<QtValue *(void *)> m_reader;
            std::function<void(void *, QtValue *)> m_writer;
            bool m_isVriting;

            friend class ::qt::type;
        };
    }

    // qt::property exposes a property to Qt. Properties are attached to a qt::type.
    //
    // Usage:
    // - Expose a named property with read and write callbacks:
    //     qt::property<T> qt_property(qt_type, "property", reader_fn, writer_fn);
    //
    // - Notify Qt that the property value has changed. (Qt will read the value using reader_fn)
    //     qt_property.notify_chaged(this);
    //
    template <typename T>
    class property : public detail::property_base
    {
    public:
        template <typename Reader, typename Writer>
        property(type *type, const char *property_name, Reader reader, Writer writer)
        {
            m_property_name = property_name;
            m_type_name = "int"; // ###

            // Register property on type for later lookup by property name.
            type->m_properties[property_name] = this;

            // Create and store generic readers and writers that wraps the
            // typed readers and writers. This allows reading and writing
            // values from non-template code using QtValue.

            // ### type deduction only works for std::mem_fn
            typedef typename Reader::argument_type ReaderInstanceType;
            typedef typename Writer::first_argument_type WriterInstanceType;

            m_reader = detail::qtvalue_reader<ReaderInstanceType, T>(reader);
            m_writer = detail::qtvalue_writer<WriterInstanceType, T>(writer);
        }

        // Called by the applicaiton to signal property value change.
        template <typename I>
        void notify_changed(I *instance)
        {
            property_base::notify_changed(instance);
        }
    };

    // qt::invokable exposes a function which Qt can call. Invokables are attached to a qt::type.
    //
    // Usage:
    //  qt::invokable qt_invokable(qt_type, callback_fn);
    //
    // [qt::invokable does currently not support callback_fns taking arguments or returning values.]
    class invokable
    {
    public:
        template <typename Fn>
        invokable(type *type, Fn fn)
        {

        }
    };

    // Main bindings API. User code creates an instance of this class "first thing"
    // in main(). Note that this is actually not first use of the bindings API:
    // qt::type and qt::property is created at static object construction time.
    class bindings
    {
    public:
        bindings()
        {
            // Create bindings with callbacks
            m_bindings = detail::qtCreateQmlBindings(this, create_object_cb, destroy_object_cb,
                                                           read_property_cb, write_property_cb);

            // Finalize types. All types and properties should be constructed
            // (as static objects) before the bindings are created.
            for (auto& type_kv : type::m_types) {

                // Create class
                const char *name = type_kv.first;
                type *type = type_kv.second;
                type->m_qt_class = qtCreateClass(m_bindings, name);

                // Create properties on class
                for (auto& property_kv : type->m_properties) {
                    const char *name = property_kv.first;
                    detail::property_base *property = property_kv.second;
                    qtCreateProperty(m_bindings, type->m_qt_class, property->type_name(), property->property_name());
                }

                qtFinalizeClass(m_bindings,  type->m_qt_class);
            }
        }

        ~bindings()
        {
            qtDestroyQmlBindings(m_bindings);
        }

        void registerInstance(type *type, void *instance, const char *identifier)
        {
            // update store instance -> type map
            m_instances[instance] = type;

            // register instance with Qt
            qtObjectCreated(m_bindings, type->m_qt_class, instance);

            // register instance with QML
            qtObjectRegister(m_bindings, instance, identifier);
        }

    private:
        std::map<void *, type *> m_instances; // instance -> type map

        // qt::bindings callbacks called by Qt for creating and destroying objects
        static void *create_object_cb(void *context, const char *class_name)
        {
            std::cerr << "Not implemented: create_object" << std::endl;
            return 0;
        }
        static void destroy_object_cb(void *context, void *object)
        {
            std::cerr << "Not implemented: destroy_object" << std::endl;
        }

        // qt::bindings callbacks called by Qt for reading and writing properties
        static detail::QtValue *read_property_cb(void *context, void *instance, const char *property_name)
        {
            bindings *b = reinterpret_cast<bindings *>(context);
            return b->m_instances[instance]->read_property(property_name, instance);
        }
        static void write_property_cb(void *context, void *instance, const char *property_name, detail::QtValue *value)
        {
            bindings *b = reinterpret_cast<bindings *>(context);
            b->m_instances[instance]->write_property(property_name, instance, value);
        }

        detail::QtQmlBindings *m_bindings;
    };

    int main(int argc, char **argv, const char *qml_file_name) {
        return detail::qtMain(argc, argv, qml_file_name);
    }

    // Further function definitions
    detail::QtValue *type::read_property(const char *property_name, void *instance)
    {
        return m_properties[property_name]->read(instance);
    }
    void type::write_property(const char *property_name, void *instance, detail::QtValue *value)
    {
        return m_properties[property_name]->write(instance, value);
    }

} // namespace qt

#endif
