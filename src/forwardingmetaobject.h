#ifndef FORWARDINGMETAOBJECT_H
#define FORWARDINGMETAOBJECT_H

#include <QtCore/QtCore>
#include <QtCore/private/qmetaobject_p.h>

#include <functional>

class QMetaObjectBuilder;
class ForwardMetaObjectBuilder
{
public:
    ForwardMetaObjectBuilder();
    ~ForwardMetaObjectBuilder();

    void setClassName(const QByteArray &name);
    void setSuperClass(const QMetaObject *metaObject);

    void addProperty(const QByteArray &propertyName, const QByteArray &typeName);
    void addSetter(const QByteArray &propertyName, const QByteArray &typeName);

    QByteArray propertyNotifySignalName(const QByteArray &propertyName, const QByteArray &typeName);


    QMetaObjectBuilder *metaObjectBuilder();
    QMetaObject *metaObject();
private:
    QMetaObjectBuilder *builder;
};
/*

class ForwardObject : public QObject
{
    // Manually expanded from Q_OBJECT macro
public:
    Q_OBJECT_CHECK
    static QMetaObject staticMetaObject;
    virtual const QMetaObject *metaObject() const;
    virtual void *qt_metacast(const char *);
    virtual int qt_metacall(QMetaObject::Call, int, void **);
private:
    Q_DECL_HIDDEN static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **);

public:
    ForwardObject(QObject *parent = 0); // Q_INVOKABLE
    ~ForwardObject();
    void setMetaObject(const QMetaObject *metaObject);
    void propertyChange(const QByteArray name);

    // public forwarding callback API
    virtual void init();
    virtual QVariant readProperty(const QByteArray &name);
    virtual void wrtiteProperty(const QByteArray &name, const QVariant &value);
private:
    friend class ForwardMetaObjectBuilder;
    // Properties
    QList<QByteArray> m_propertyNames;

    const QMetaObject *m_metaObject;
};


class SimpleForwardObject : public QObject, QObjectCallbackInterface
{
public:
    Q_OBJECT_CHECK
    static QMetaObject staticMetaObject;
    const QMetaObject *metaObject() const;
    int qt_metacall(QMetaObject::Call _c, int _id, void **_a);

    void setMetaObject(const QMetaObject *metaObject);

    QVariant readProperty(const QByteArray &name);
    void wrtiteProperty(const QByteArray &name, const QVariant &value);
private:
    const QMetaObject *m_metaObject;
};

*/

/*
class QObjectCallbackInterface
{
public:
    virtual QVariant readProperty(const QByteArray &name) = 0;
    virtual void wrtiteProperty(const QByteArray &name, const QVariant &value) = 0;
};
QObjectCallbackInterface *qobjectCallbackInterface_cast(QObject *object);
*/

template <typename BASE>
class SimpleForwardObjectT : public BASE
{
public:
    Q_OBJECT_CHECK
    static QMetaObject staticMetaObject;
    const QMetaObject *metaObject() const;
    void *qt_metacast(const char *_clname);
    int qt_metacall(QMetaObject::Call _c, int _id, void **_a);

    void setMetaObject(const QMetaObject *metaObject);

    virtual QVariant readProperty(const QByteArray &name);
    virtual void wrtiteProperty(const QByteArray &name, const QVariant &value);
private:
    const QMetaObject *m_metaObject;
};

template <typename BASE>
const QMetaObject *SimpleForwardObjectT<BASE>::metaObject() const
{
    //qDebug() << __PRETTY_FUNCTION__;
    return m_metaObject;
}

template <typename BASE>
void *SimpleForwardObjectT<BASE>::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, "ForwardingMetaObjectT"))
        return static_cast<void*>(const_cast< SimpleForwardObjectT<BASE>*>(this));
    return BASE::qt_metacast(_clname);
}


template <typename BASE>
int SimpleForwardObjectT<BASE>::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
//    qDebug() << this << "SimpleForwardObjectT::qt_metacall" << _id;
    _id = BASE::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;

    int ownMethodCount = m_metaObject->methodCount() - m_metaObject->methodOffset();
    int ownPropertyCount = m_metaObject->propertyCount() - m_metaObject->propertyOffset();
    int ownId = _id + m_metaObject->propertyOffset();

    if (_c == QMetaObject::InvokeMetaMethod) {

    } else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        //qDebug() << "  qt_metacall ReadProperty" << _id << ownPropertyCount;
        QMetaProperty property = m_metaObject->property(ownId);
        QByteArray name = property.name();
        QVariant value = readProperty(name);
        // ### now _v is a T *, which we want to copy the value into.
        int typeSize = QMetaType::sizeOf(property.type());
        if (typeSize != 0)
            memcpy(_v, value.constData(), QMetaType::sizeOf(property.type()));
        else
            qDebug() << "ForwardObject::qt_metacall: Unsupported type" << property.typeName();

        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        //qDebug() << "  qt_metacall WriteProperty" << _id << ownPropertyCount << m_metaObject->propertyCount() << m_metaObject->propertyOffset();
        QMetaProperty property = m_metaObject->property(ownId);
        QByteArray name = property.name();
        QVariant value = QVariant(property.type(), _v);
  //      qDebug() << "  qt_metacall WriteProperty" << name << value;
        wrtiteProperty(name, value);
        _id -= ownPropertyCount;
    }
    return _id;
}

template <typename BASE>
void SimpleForwardObjectT<BASE>::setMetaObject(const QMetaObject *metaObject)
{
    SimpleForwardObjectT<BASE>::staticMetaObject = *metaObject;
    m_metaObject = metaObject;
}

template <typename BASE>
QVariant SimpleForwardObjectT<BASE>::readProperty(const QByteArray &name)
{
    qDebug() << __PRETTY_FUNCTION__ << name;
    return QVariant();
}

template <typename BASE>
void SimpleForwardObjectT<BASE>::wrtiteProperty(const QByteArray &name, const QVariant &value)
{
    qDebug() << __PRETTY_FUNCTION__ << name << value;
}

template <typename BASE>
QMetaObject SimpleForwardObjectT<BASE>::staticMetaObject = {
    { 0, 0, 0, 0, 0, 0 }
};
#endif
