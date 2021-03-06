#ifndef PLEXY_YOUTUBE_H
#define PLEXY_YOUTUBE_H

#include <plexy.h>
#include <controllerinterface.h>
#include "authwidget.h"

class AuthPlugin : public PlexyDesk::ControllerInterface
{
    Q_OBJECT

public:
    AuthPlugin(QObject *object = 0);
    virtual ~AuthPlugin();
    PlexyDesk::AbstractDesktopWidget *defaultView();

    void revokeSession(const QVariantMap &args);

    void setViewRect(const QRectF &rect);

private:
    PlexyDesk::AuthWidget *mWidget;
};

#endif
