#include "iconloader.h"


IconLoader::IconLoader(QObject *parent) : QObject(parent)
{
   mime = new QPlexyMime();
//   icp = new IconProvider();
   model = new QDeclarativeFolderListModel();
   model->setFolder(QUrl("."));
   connect(mime,SIGNAL(genericIconNameMime(MimeTypePair)),this,SLOT(mimeFound(MimeTypePair)));
}

QString IconLoader::folder()
{
   return model->folder().toString();
}

void IconLoader::setFolder(QString &name)
{
   QString curr = model->folder().toString();
   model->setFolder(QUrl(name));
   //if (!model->isFolder())
	//model->setFolder(curr);
}

bool IconLoader::isFolder(int index)
{
   return model->isFolder(index);
}

QString IconLoader::mimeIcon()
{
   if (!mimeType.isEmpty())
      return m_pair.second;
   else
      return "mime type unavailable";
}

void IconLoader::setMimeIcon(QString &mimetype)
{
   mime->genericIconName(mimetype);
}

void IconLoader::mimeFound(MimeTypePair pair)
{
   m_pair = pair;
   qDebug()<<pair.first<<"\t:"<<pair.second;
}

