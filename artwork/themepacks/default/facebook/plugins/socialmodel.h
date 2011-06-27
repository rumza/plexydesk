#ifndef SOCIALMODEL_H
#define SOCIALMODEL_H

#include <qdeclarative.h>
#include <QDeclarativeParserStatus>
#include <QString>
#include "socialaccessmanager.h"

QT_MODULE(Declarative)

class QDeclarativeContext;


class SocialModel : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QString serviceEngine READ getServiceEngine WRITE setServiceEngine)
public:
    SocialModel(QObject *parent = 0);
    Q_INVOKABLE void requestService(QString serviceName, QString data);
    void setServiceEngine(QString service);
    QString getServiceEngine();
    Q_INVOKABLE QString getError();
    void classBegin(){}
    void componentComplete(){}
signals:
    void error();
private:
    QString m_serviceEngine;
    QString m_error;
    SocialAccessManager m_api;

};
QML_DECLARE_TYPE(SocialModel)

#endif // SOCIALMODEL_H
