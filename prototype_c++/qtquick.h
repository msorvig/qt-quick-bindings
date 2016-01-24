
namespace qt {

    template <typename T>
    class type
    {
    public:
        type(const char *typeName);
        
    };

    template <typename T>
    type<T>::type(const char *typeName)
    {
    
    }
    
    namespace detail {
        // std::function<R, (A *)> -> std::function<R, (void *)>
        template <typename R, typename A>
        struct erase1 {
        public:
            template <typename T> erase1(T fn) :m_fn(fn) { }
            R operator()(void *a) { return m_fn(reinterpret_cast<A *>(a)); }
        private:
            std::function<R(A *)> m_fn;
        };

        // std::function<R, (A *, B)> -> std::function<R, (void *, B)>
        template <typename R, typename A, typename B>
        struct erase2 {
        public:
            template <typename T> erase2(T fn) :m_fn(fn) { }
            R operator()(void *a, B b) { return m_fn(reinterpret_cast<A *>(a), b); }
        private:
            std::function<R(A *, B)> m_fn;
        };
    }

    template <typename T>
    class property
    {
    public:
        template <typename C, typename Reader, typename Writer>
        property(type<C> *type, const char *propertyName, Reader reader, Writer writer)
            :m_reader(detail::erase1<T, C>(reader))
            ,m_writer(detail::erase2<void, C, T>(writer))
        {
            
        }
        
        void notify_changed()
        {
            
        }
        
    private:
        // Store reader and writer functions as with 'void *' to
        // avoid templating qt::property on the qt::type template
        // type (this would spill out to the user API).
        std::function<T(void *)> m_reader;
        std::function<void(void *, T)> m_writer;
    };

    class invokable
    {
    public:
        template <typename C, typename Fn>
        invokable(type<C> *type, Fn fn)
        {
        
        }
    };
    
    
    class bindings
    {
    public:
        bindings()
        {
            
        }

        template <typename C>
        void registerInstance(const type<C> &type, const char *identifier, void *instance)
        {
    
        }

        int main(const char *qmlFileName)
        {
            return 0;
        }
    };
}

