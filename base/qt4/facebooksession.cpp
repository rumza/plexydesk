#include "facebooksession.h"
#include <jsonhandler.h>
#include <plexyconfig.h>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

class FacebookSession::Private
{
public:
    Private() {}
    ~Private() {}
  QNetworkAccessManager *mNtManager;
  QNetworkCookieJar *mCookie;
  QNetworkReply *mReply;
  QString mToken;
  QByteArray mData;
  QHash<QString,QVariant> mResult;
};

FacebookSession::FacebookSession(QObject *parent) :
    QObject(parent), d(new Private)
{
    d->mNtManager = new QNetworkAccessManager(this);
    d->mCookie = new QNetworkCookieJar(this);
    d->mNtManager->setCookieJar(d->mCookie);
    //todo proxy setup;
}

void FacebookSession::makeRequest(const QString &url)
{
   if(hasToken())
   {
      QUrl ntUrl (url + (QLatin1String ("?access_token=") + d->mToken));
      QNetworkRequest request;
      request.setUrl (ntUrl);

      d->mReply = d->mNtManager->get(request);
      qDebug() << Q_FUNC_INFO << d->mReply->readAll();
      connect(d->mReply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   }
}


void FacebookSession::onReadyRead()
{
    qDebug() << Q_FUNC_INFO ;

    QNetworkReply *reply = qobject_cast<QNetworkReply*> (sender());

    if (!reply) 
      return;
  
   d->mData = reply->readAll();
   JsonHandler *mJsonHandle;
   JsonData result = mJsonHandle->property(d->mData, "data");
   
   if (result.type() == JsonData::Error) {
     qDebug() << Q_FUNC_INFO << "Error";
     return;
   }
 
   d->mResult = result.data();
   qDebug () << Q_FUNC_INFO << d->mData;
   Q_EMIT ready();
}

QByteArray FacebookSession::rawData() const
{
   return d->mData;
}

QHash<QString,QVariant> FacebookSession::parsedData() const
{
   return d->mResult;
}

bool FacebookSession::hasToken() const
{
   PlexyDesk::Config *config = PlexyDesk::Config::getInstance();
   config->coreSettings()->beginGroup("facebook_plugin");
   QString token = config->coreSettings()->value("access_token").toString(); 
   config->coreSettings()->endGroup();

   if (token.isEmpty() || token.isNull()) {
       return 0;
   }

  d->mToken = token;

  return true;
}

void FacebookSession::requestFriendsList()
{
   this->makeRequest("http://graph.facebook.com/me/friends");
}


