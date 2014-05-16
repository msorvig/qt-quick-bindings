#include "forwardingmetaobject.h"

#include <QtCore/QtCore>
#include <QtCore/private/qmetaobjectbuilder_p.h>

#include <QtQuick/QQuickItem>

ForwardMetaObjectBuilder::ForwardMetaObjectBuilder()
{
    builder = new QMetaObjectBuilder;
    builder->setSuperClass(&QQuickItem::staticMetaObject);
    //builder->setStaticMetacallFunction(ForwardObject::qt_static_metacall);
}

ForwardMetaObjectBuilder::~ForwardMetaObjectBuilder()
{
    delete builder;
}

void ForwardMetaObjectBuilder::setClassName(const QByteArray &name)
{
    builder->setClassName(name);
}

void ForwardMetaObjectBuilder::setSuperClass(const QMetaObject *metaObject)
{
    builder->setSuperClass(metaObject);
}

void ForwardMetaObjectBuilder::addProperty(const QByteArray &propertyName, const QByteArray &typeName)
{
    // names
    QByteArray signalName = propertyNotifySignalName(propertyName, typeName);
    QByteArray signalParameterName = "newValue";

    // property
    QMetaPropertyBuilder prop = builder->addProperty(propertyName, typeName);
    // qDebug() << "property" << propertyName << prop.index();

    // notifier
    QMetaMethodBuilder intPropChanged = builder->addSignal(signalName);
    intPropChanged.setParameterNames(QList<QByteArray>() << signalParameterName);
    prop.setNotifySignal(intPropChanged);
}

QByteArray ForwardMetaObjectBuilder::propertyNotifySignalName(const QByteArray &propertyName,
                                                              const QByteArray &typeName)
{
    return propertyName + "Changed(" + typeName + ")";
}

QMetaObjectBuilder *ForwardMetaObjectBuilder::metaObjectBuilder()
{
    return builder;
}

QMetaObject *ForwardMetaObjectBuilder::metaObject()
{
//    qDebug() << __PRETTY_FUNCTION__;

    builder->addConstructor(builder->className() + "(QObject*)");
    builder->addConstructor(builder->className() + "()");

    // QMetaMethodBuilder foo = builder.addMethod("foo(QString)");
    // foo.setReturnType("void");
    // foo.setParameterNames(QList<QByteArray>() << "qstringArg");

    // setter?
    // QByteArray slotName = "voidSlot" + typeName + "(" + typeName + ")";
    // QMetaMethodBuilder voidSlotInt = builder.addSlot(slotName);
    // voidSlotInt.setParameterNames(QList<QByteArray>() << signalParameterName);

    // Create the new metaOBejct
    QMetaObject *metaObject = builder->toMetaObject();

    // Set the static meta object here in order for it to be
    // a valid during reigstration with QML. This will of
    // course override any previously set meta object.
    //ForwardObject::staticMetaObject = *metaObject;
    //SimpleForwardObject::staticMetaObject = *metaObject;
    return metaObject;
}
/*
QMetaObject ForwardObject::staticMetaObject = {
    { 0, 0, 0, 0, 0, 0 }
};

QMetaObject SimpleForwardObject::staticMetaObject = {
    { 0, 0, 0, 0, 0, 0 }
};


ForwardObject::ForwardObject(QObject *parent)
    : QObject(parent), m_metaObject(&staticMetaObject)
{

}

void ForwardObject::setMetaObject(const QMetaObject *metaObject)
{
    m_metaObject = metaObject;
}

void ForwardObject::propertyChange(const QByteArray name)
{
    //QByteArray signalName = name + "Changed(" + typeName + ")";
    //int signal = m_metaObject->indexOfSignal(signalName);
    //char *argv = 0;
    //m_metaObject->activate(this, signal, &argv);
}

ForwardObject::~ForwardObject()
{
    //free(m_metaObject);
}

void ForwardObject::init()
{

}

QVariant ForwardObject::readProperty(const QByteArray &name)
{
    qDebug() << __PRETTY_FUNCTION__ << name;
    return QVariant();
}

void ForwardObject::wrtiteProperty(const QByteArray &name, const QVariant &value)
{
    qDebug() << __PRETTY_FUNCTION__ << name << value;
}

void ForwardObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    qDebug() << __PRETTY_FUNCTION__ << _o << _id;
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: {
            ForwardObject *_r = new ForwardObject((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r;
        } break;
        case 1: {
            ForwardObject *_r = new ForwardObject();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r;
        } break;
        default: {
            QMetaMethod ctor = _o->metaObject()->constructor(_id);
            qFatal("You forgot to add a case for CreateInstance %s", ctor.methodSignature().constData());
          }
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(_o->metaObject()->cast(_o));
        ForwardObject *_t = static_cast<ForwardObject *>(_o);
        //qDebug() << "  qt_static_metacall InvokeMetaMethod" << _id;
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        //qDebug() << "  qt_static_metacall IndexOfMethod" << *func;
        *result = 0;
    }
}

const QMetaObject *ForwardObject::metaObject() const
{
    qDebug() << __PRETTY_FUNCTION__;
    return m_metaObject;
}

void *ForwardObject::qt_metacast(const char *_clname)
{
    qDebug() << __PRETTY_FUNCTION__;
    if (!_clname) return 0;
    if (!strcmp(_clname, "ForwardingMetaObject"))
        return static_cast<void*>(const_cast< ForwardObject*>(this));
    return QObject::qt_metacast(_clname);
}


int ForwardObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    qDebug() << this << __PRETTY_FUNCTION__;
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    int ownMethodCount = m_metaObject->methodCount() - m_metaObject->methodOffset();
    int ownPropertyCount = m_metaObject->propertyCount() - m_metaObject->propertyOffset();
    int ownId = _id + m_metaObject->propertyOffset();
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < ownMethodCount)
            qt_static_metacall(this, _c, _id, _a);
        _id -= ownMethodCount;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
         qDebug() << "  qt_metacall ReadProperty" << _id << ownPropertyCount;
         QMetaProperty property = m_metaObject->property(ownId);
        QByteArray name = property.name();
        QVariant value = readProperty(name);
        // ### now _v is a T *, which we want to copy the value into.
        switch (property.type()) {
           case QMetaType::Int: *static_cast<int *>(_v) = value.toInt(); break;
            case QMetaType::QString: *static_cast<QString *>(_v) = value.toString(); break;
            default:
                qDebug() << "ForwardObject::qt_metacall: Unsupported type" << property.typeName();
        };

        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
                qDebug() << "  qt_metacall WriteProperty" << _id << ownPropertyCount << m_metaObject->propertyCount() << m_metaObject->propertyOffset();
        QMetaProperty property = m_metaObject->property(ownId);
        QByteArray name = property.name();
        QVariant value = QVariant(property.type(), _v);
        wrtiteProperty(name, value);
        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= ownPropertyCount;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

void SimpleForwardObject::setMetaObject(const QMetaObject *metaObject)
{
    qDebug() << "SimpleForwardObject setMetaObject" << metaObject;
    m_metaObject = metaObject;
}

const QMetaObject *SimpleForwardObject::metaObject() const
{
    qDebug() << __PRETTY_FUNCTION__;
    return m_metaObject;
}

int SimpleForwardObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    //qDebug() << this << __PRETTY_FUNCTION__ << _id;
    _id = QObject::qt_metacall(_c, _id, _a);
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
        //MetaType::convert(
         //QVariant::convert(c
        switch (property.type()) {
           // case QMetaType::Int: *static_cast<int *>(_v) = value.toInt(); break;
            //case QMetaType::QString: *static_cast<QString *>(_v) = value.toString(); break;
            default:
                qDebug() << "ForwardObject::qt_metacall: Unsupported type" << property.typeName();
        };

        _id -= ownPropertyCount;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
       // qDebug() << "  qt_metacall WriteProperty" << _id << ownPropertyCount << m_metaObject->propertyCount() << m_metaObject->propertyOffset();
        QMetaProperty property = m_metaObject->property(ownId);
        QByteArray name = property.name();
        QVariant value = QVariant(property.type(), _v);

        wrtiteProperty(name, value);
        _id -= ownPropertyCount;
    }
    return _id;
}
QVariant SimpleForwardObject::readProperty(const QByteArray &name)
{
    qDebug() << __PRETTY_FUNCTION__ << name;
    return QVariant();
}

void SimpleForwardObject::wrtiteProperty(const QByteArray &name, const QVariant &value)
{
    qDebug() << __PRETTY_FUNCTION__ << name << value;
}

*/
