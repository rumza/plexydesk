#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <config.h>
#include <iconjob.h>
#include <plexy.h>

#include <QtCore>

namespace PlexyDesk
{

class IconProvider : public QObject
{
    Q_OBJECT
public:
    IconProvider();
    IconJobPtr requestIcon(const QString &name, const QString &);
    QString getIconPath(const QString &name, const QString &size);
private:
    class Private;
    Private *const d;
};

typedef QSharedPointer<IconProvider> IconProviderPtr;
}

#endif // ICONPROVIDER_H
