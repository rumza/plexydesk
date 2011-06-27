#include "socialmodel.h"

SocialModel::SocialModel(QObject *parent) :
    QObject(parent)
{
}
QString SocialModel::getError()
{
    return m_error;
}

void SocialModel::setServiceEngine(QString service)
{
    m_serviceEngine = service;
    m_api.setService(m_serviceEngine);
}

void SocialModel::requestService(QString serviceName, QString data)
{
    QVariantMap m_map;
    m_map["service"] = QVariant(serviceName);
    //data parameter should look like "key,value,key,value,key,..."
    QStringList datagrid = data.split(",");
    if (datagrid.length()%2 != 0)
    {
        m_error = "invalid number of params";
        emit error();
        return;
    }
    for (int i=0;i < datagrid.length() ;i=i +2)
    {
        m_map[datagrid.at(i)] = QVariant(datagrid.at(i+1));
    }
    m_api.requestService(m_map);
}

QString SocialModel::getServiceEngine()
{
    return m_serviceEngine;
}
