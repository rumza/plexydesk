#include "plugin.h"

void QmlFolderListModelPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<QDeclarativeFolderListModel>(uri,1,0,"FolderListModel");
    qmlRegisterType<IconLoader>(uri,1,0,"IconLoader");
}

Q_EXPORT_PLUGIN2(libiconcontainer, QmlFolderListModelPlugin);

