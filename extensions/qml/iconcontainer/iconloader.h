#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <qplexymime.h>
#include <iconprovider.h>
#include "qdeclarativefolderlistmodel.h"
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/QDeclarativeParserStatus>

QT_MODULE(Declarative)

class QDeclarativeContext;


typedef QPair<QString, QString> MimeTypePair;

class IconLoader : public QObject, public QDeclarativeParserStatus
{
   Q_OBJECT
   Q_INTERFACES(QDeclarativeParserStatus)
public:
   IconLoader(QObject *parent=0);
   virtual ~IconLoader();
   Q_PROPERTY(QString folder READ folder WRITE setFolder);
   Q_PROPERTY(QString mimeIcon READ mimeIcon WRITE setMimeIcon);	
   QString folder();
   void setFolder(QString &name);
   QString mimeIcon();
   void setMimeIcon(QString &mimetype);
   Q_INVOKABLE bool isFolder(int index);
   virtual void classBegin();
   virtual void componentComplete();
private slots:
   void mimeFound(MimeTypePair pair);
private:
   QPlexyMime *mime;
//   IconProvider *icp;
   QDeclarativeFolderListModel *model;
   QString mimeType;
   MimeTypePair m_pair;
};


QML_DECLARE_TYPE(IconLoader)

#endif
