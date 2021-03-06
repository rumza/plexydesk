/*******************************************************************************
* This file is part of PlexyDesk.
*  Maintained by : Siraj Razick <siraj@kde.org>
*  Authored By  :
*
*  PlexyDesk is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  PlexyDesk is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with PlexyDesk. If not, see <http://www.gnu.org/licenses/lgpl.html>
*******************************************************************************/

#include <config.h>

#include <QDir>
#include <QtDebug>
#include <QGLWidget>
#include <QFutureWatcher>
#include <QSharedPointer>
#include <QPropertyAnimation>
#include <QGraphicsGridLayout>
#include <QGraphicsDropShadowEffect>
#include <QDomDocument>

#include <abstractdesktopwidget.h>
#include <controllerinterface.h>
#include <pluginloader.h>

#include "controllerinterface.h"
#include "abstractdesktopview.h"

/**
  \class PlexyDesk::AbstractDesktopView

  \brief Base class for creating DesktopViews

  \fn PlexyDesk::AbstractDesktopView::enableOpenGL()

  \param state Method to enable OpenGL rendering on the view, internally
               it assigns a QGLWidget to the viewport.

  \fn PlexyDesk::AbstractDesktopView::showLayer()

   \fn  PlexyDesk::AbstractDesktopView::addExtension()
   \brief Adds an Widget Extension to Plexy Desktop, give the widget
   name in string i.e "clock" or "radio", the internals will
   take care of the loading the widget if a plugin matching the name is
   found.

   \param name String name of the widget as specified by the desktop file

   \param layerName Name of the layer you want add the widget to

**/
namespace PlexyDesk
{

class AbstractDesktopView::PrivateAbstractDesktopView
{
public:
    PrivateAbstractDesktopView() {}
    ~PrivateAbstractDesktopView()
    {
        if (mSessionTree)
            delete mSessionTree;

        mControllerMap.clear();

        if (mDesktopWidget)
            delete mDesktopWidget;
    }

    QMap<QString, QSharedPointer<ControllerInterface> > mControllerMap;
    AbstractDesktopWidget *mBackgroundItem;
    QDomDocument *mSessionTree;
    QDomElement mRootElement;
    QDesktopWidget *mDesktopWidget;
    QString mBackgroundControllerName;
};

AbstractDesktopView::AbstractDesktopView(QGraphicsScene *scene, QWidget *parent) :
    QGraphicsView(scene, parent), d(new PrivateAbstractDesktopView)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);

    d->mDesktopWidget = new QDesktopWidget();
    d->mBackgroundItem = 0;

    d->mSessionTree = new QDomDocument("Session");
    d->mSessionTree->appendChild(d->mSessionTree->createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\""));
    d->mRootElement = d->mSessionTree->createElement("session");
    d->mSessionTree->appendChild(d->mRootElement);

    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    setFrameStyle(QFrame::NoFrame);
}

AbstractDesktopView::~AbstractDesktopView()
{
    qDebug() << Q_FUNC_INFO;
    delete d;
}

void AbstractDesktopView::enableOpenGL(bool state)
{
    if (state) {
        setViewport(new QGLWidget(QGLFormat(
                        QGL::DoubleBuffer )));
        setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
        setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
        setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    } else {
        setViewport(new QWidget);
        setCacheMode(QGraphicsView::CacheNone);
        setOptimizationFlags(QGraphicsView::DontSavePainterState);
        setOptimizationFlag(QGraphicsView::DontClipPainter);
        setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    }
}

bool AbstractDesktopView::setBackgroundController(const QString &controllerName)
{
    //TODO: error handling
    // delete the current background source before setting a new one

    QSharedPointer<ControllerInterface> controller =
            (PlexyDesk::PluginLoader::getInstance()->controller(controllerName));

    d->mControllerMap[controllerName] = controller;

    if (!controller.data()) {
        qWarning() << Q_FUNC_INFO << "Error loading extension" << controllerName;
        return false;
    }

    for (int i = 0 ; i < d->mDesktopWidget->screenCount() ; i++) {
        qDebug() << Q_FUNC_INFO << i;
        d->mBackgroundItem = (AbstractDesktopWidget*) controller->defaultView();

        scene()->addItem(d->mBackgroundItem);

        d->mBackgroundItem->setContentRect(d->mDesktopWidget->screenGeometry(i));

        d->mBackgroundItem->show();
        d->mBackgroundItem->setZValue(-1);

        controller->setViewport(this);
        controller->setControllerName(controllerName);
    }
    return true;
}

void AbstractDesktopView::addController(const QString &controllerName)
{
    if (d->mControllerMap.keys().contains(controllerName))
        return;

    QSharedPointer<ControllerInterface> controller =
            (PlexyDesk::PluginLoader::getInstance()->controller(controllerName));

    if (!controller.data()) {
        qWarning() << Q_FUNC_INFO << "Error loading extension" << controllerName;
        return;
    }

    connect(controller.data(), SIGNAL(spawnView(AbstractDesktopWidget*)), this, SLOT(addWidgetToView(AbstractDesktopWidget*)));

    d->mControllerMap[controllerName] = controller;

    QGraphicsItem *defaultView = controller->defaultView();

    scene()->addItem(defaultView);

    defaultView->show();

    controller->setViewport(this);
    controller->setControllerName(controllerName);
}

QStringList AbstractDesktopView::currentControllers() const
{
    QStringList rv = d->mControllerMap.keys();
    rv.removeOne(d->mBackgroundControllerName);

    return rv;
}

void AbstractDesktopView::setControllerRect(const QString &controllerName, const QRectF &rect)
{
    if (d->mControllerMap[controllerName]) {
        d->mControllerMap[controllerName]->setViewRect(rect);
    }

    QDomElement widget = d->mSessionTree->createElement("widget");
    widget.setAttribute("controller", controllerName);
    QDomElement geometry = d->mSessionTree->createElement("geometry");
    geometry.setAttribute("x", rect.x());
    geometry.setAttribute("y", rect.y());
    geometry.setAttribute("width", rect.width());
    geometry.setAttribute("height", rect.height());
    widget.appendChild(geometry);
    d->mRootElement.appendChild(widget);

    qDebug() << Q_FUNC_INFO << d->mSessionTree->toString();
    Q_EMIT sessionUpdated(d->mSessionTree->toString());
}

QSharedPointer<ControllerInterface> AbstractDesktopView::controllerByName(const QString &name)
{
    return d->mControllerMap[name];
}

void AbstractDesktopView::dropEvent(QDropEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    if (this->scene()) {
        qDebug() << Q_FUNC_INFO;
        QList<QGraphicsItem *> items = scene()->items(event->pos());

        Q_FOREACH(QGraphicsItem *item, items) {

            QGraphicsObject *itemObject = item->toGraphicsObject();

            if (!itemObject) {
                continue;
            }

            AbstractDesktopWidget *widget = qobject_cast<AbstractDesktopWidget*> (itemObject);

            if (!widget || !widget->controller())
                continue;

            qDebug() << Q_FUNC_INFO << "handle drop event";

            widget->controller()->handleDropEvent(widget, event);
            return;
        }
    }

    scene()->update(this->sceneRect());
    event->acceptProposedAction();
}

void AbstractDesktopView::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void AbstractDesktopView::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void AbstractDesktopView::addWidgetToView(AbstractDesktopWidget *widget)
{
    QGraphicsItem *item = (AbstractDesktopWidget*) widget;
    scene()->addItem(item);
    item->show();
}

void AbstractDesktopView::sessionDataForController(const QString &controllerName, const QString &key, const QString &value)
{
    QDomNodeList widgetNodeList = d->mSessionTree->documentElement().elementsByTagName("widget");

    qDebug() << Q_FUNC_INFO << widgetNodeList.count();

    for(int index = 0; index < widgetNodeList.count(); index++) {
        QDomElement widgetElement = widgetNodeList.at(index).toElement();

        qDebug() << Q_FUNC_INFO << widgetElement.attribute("controller");
        if (widgetElement.attribute("controller") != controllerName)
            continue;

        if (widgetElement.hasChildNodes()) {
            QDomElement argElement = widgetElement.firstChildElement("arg");

            if (argElement.isNull()) {
                QDomElement keyTag = d->mSessionTree->createElement("arg");
                keyTag.setAttribute(key, value);
                widgetElement.appendChild(keyTag);
            } else
                argElement.setAttribute(key, value);

        }
    }

    Q_EMIT sessionUpdated(d->mSessionTree->toString());
}

void AbstractDesktopView::restoreViewFromSession(const QString &sessionData)
{
    if (d->mSessionTree) {
        QString errorMsg;
        d->mSessionTree->setContent(sessionData, &errorMsg);
        qDebug() << Q_FUNC_INFO <<  errorMsg;
    }

    QDomNodeList widgetNodeList = d->mSessionTree->documentElement().elementsByTagName("widget");

    for(int index = 0; index < widgetNodeList.count(); index++) {
        QDomElement widgetElement = widgetNodeList.at(index).toElement();

        addController(widgetElement.attribute("controller"));
        QSharedPointer<ControllerInterface> iface = controllerByName(widgetElement.attribute("controller"));

        if (widgetElement.hasChildNodes()) {
            QDomElement argElement = widgetElement.firstChildElement("arg");

            if (!argElement.isNull()) {
                QDomNamedNodeMap attrMap = argElement.attributes();
                QVariantMap args;
                for (int attrIndex = 0; attrIndex < attrMap.count(); attrIndex++) {
                    QDomNode attributeNode = attrMap.item(attrIndex);
                    QString key = attributeNode.toAttr().name();
                    QString value = attributeNode.toAttr().value();
                    args[key] = QVariant(value);
                }

                if (iface) {
                    iface->revokeSession(args);
                }
            }

            //restore geometry
            QDomElement rectElement = widgetElement.firstChildElement("geometry");
            if (!rectElement.isNull()) {
                QDomAttr x = rectElement.attributeNode("x");
                QDomAttr y = rectElement.attributeNode("y");

                QDomAttr widthAttr = rectElement.attributeNode("width");
                QDomAttr heightAttr = rectElement.attributeNode("height");

                QRectF geometry (x.value().toFloat(), y.value().toFloat(), widthAttr.value().toFloat(), heightAttr.value().toFloat());

                if(iface) {
                    iface->setViewRect(geometry);
                }
            }
        }
    }
}

}
