#ifndef FBTEST_H
#define FBTEST_H

#include <QObject>
#include <dataplugin.h>
#include <plexy.h>

using namespace PlexyDesk;

class fbtest : public PlexyDesk::DataPlugin
{
    Q_OBJECT
public:
    fbtest(QObject *parent = 0);
    void runTest(int id);
    QVariantMap readAll(){}
public slots:
    void listen();
    void pushData(QVariant &data){Q_UNUSED(data);}
private:
    PlexyDesk::DataPlugin *fbengine;

};

#endif // FBTEST_H
