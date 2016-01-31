#ifndef QMLBINDINGS_P_H
#define QMLBINDINGS_P_H

#include "qmlbindings.h"

#include "forwardingmetaobject.h"
#include "qtwindowcontrolleritem.h"
#include <QQuickItem>
#include <QQuickPaintedItem>

typedef struct QtQmlBindings_t QtQmlBindings;
typedef struct QtClass_t QtClass;

class QmlBindingsForwardingObject : public SimpleForwardObjectT<QObject>
{
Q_OBJECT
public:
    QmlBindingsForwardingObject(QtQmlBindings *bindings, void *userInstance, const QMetaObject *metaObject);
    QVariant readProperty(const QByteArray &name);
    void wrtiteProperty(const QByteArray &name, const QVariant &valueVariant);
    void propertyChange(const QByteArray name);

    QtQmlBindings *m_bindings;
    void *m_userInstance;
};

class QmlBindingsPaintedItem : public SimpleForwardObjectT<QQuickPaintedItem>
{
Q_OBJECT
public:
    QmlBindingsPaintedItem(QtQmlBindings *bindings, void *userInstance, const QMetaObject *metaObject);
    QVariant readProperty(const QByteArray &name);
    void wrtiteProperty(const QByteArray &name, const QVariant &valueVariant);
    void propertyChange(const QByteArray name);
    void paint(QPainter *painter);

    QtQmlBindings *m_bindings;
    void *m_userInstance;
};

class QmlBindingsForwardingWindowController : public SimpleForwardObjectT<QtWindowControllerItem>
{
Q_OBJECT
public:
    QmlBindingsForwardingWindowController(QtQmlBindings *bindings, void *userInstance, const QMetaObject *metaObject);
    QVariant readProperty(const QByteArray &name);
    void wrtiteProperty(const QByteArray &name, const QVariant &valueVariant);
    void propertyChange(const QByteArray name);

    QtQmlBindings *m_bindings;
    void *m_userInstance;
};


#endif
