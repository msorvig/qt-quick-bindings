#include "qtwindowcontrolleritem.h"

#include <QtGui/QWindow>
#include <QtQuick/QQuickWindow>

QtWindowControllerItem::QtWindowControllerItem(QQuickItem *parent)
    : QQuickItem(parent)
    , m_controlledWindow(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(onWindowChanged(QQuickWindow*)));
    connect(this, SIGNAL(visibleChanged()), this, SLOT(onVisibleChanged()));
}

void QtWindowControllerItem::setWindow(QWindow *window)
{
    qDebug() << "QtWindowControllerItem::setWindow" << window;
    m_controlledWindow = window;
}

void QtWindowControllerItem::componentComplete()
{
   QQuickItem::componentComplete();
}

void QtWindowControllerItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    qDebug() << "QtWindowControllerItem::geometryChanged" << newGeometry << oldGeometry;
    m_controlledWindow->setGeometry(newGeometry.toRect());
}

void QtWindowControllerItem::onWindowChanged(QQuickWindow* window)
{
    if (!m_controlledWindow)
        return;

    qDebug() << "QtWindowControllerItem::setParent" << window;
    m_controlledWindow->setParent(window);
}

void QtWindowControllerItem::onVisibleChanged()
{
    qDebug() << "QtWindowControllerItem::onVisibleChanged" << isVisible();
    m_controlledWindow->setVisible(isVisible());
}
