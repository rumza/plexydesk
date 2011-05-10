#include "iconprovider.h"
#include <plexyconfig.h>

#include <QPixmap>
#include <QQueue>
#include <QSettings>
#include <QString>

namespace PlexyDesk
{
class IconProvider::Private
{
public:
    Private() {
    }
    ~Private() {
    }
    QStringList iconpaths;

};

IconProvider::IconProvider() : d(new Private)
{
}

IconJobPtr IconProvider::requestIcon(const QString &name, const QString &size)
{
    QSharedPointer<IconJob> obj =
         QSharedPointer<IconJob>(new IconJob(this), &QObject::deleteLater);
    obj->requestIcon(name, size);
    return obj;
}
QString IconProvider::getIconPath(const QString &name, const QString &size)
{
   IconJobPtr ptr = requestIcon(name,size);
   if (!ptr->iconPixmap().isNull())
	return ptr->getFullPath();
   //only for testing purposes
   //have to add a dynamic path for the release
   return "/usr/share/plexy/skins/default/icons/crystal/48x48/apps";
}
}
