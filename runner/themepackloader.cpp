#include "themepackloader.h"
#include <config.h>
#include <QDebug>
#include <QStringList>
#include <QDir>
#include <QDesktopWidget>
#include <QRect>

const QString themePackPath = QString("%1/%2").arg(PLEXPREFIX).arg("/share/plexy/themepack");

class ThemepackLoader::ThemepackLoaderPrivate
{
public:
    ThemepackLoaderPrivate() {}
    ~ThemepackLoaderPrivate() {}

    QSettings *mSettings;
    QString mThemeCfgFile;
    QString mBasePath;
    QString mThemeName;
};

ThemepackLoader::ThemepackLoader(const QString &themeName, QObject *parent) :
    QObject(parent), d (new ThemepackLoaderPrivate)
{
    d->mThemeName = themeName;
    QDir mainConfig(QString("%1/%2/").arg(themePackPath).arg(themeName));
    qDebug() << Q_FUNC_INFO << themeName;
    d->mSettings = new QSettings(QDir::toNativeSeparators(
                                 mainConfig.absoluteFilePath("main.cfg")),
                             QSettings::IniFormat, parent);

    d->mThemeCfgFile = QDir::toNativeSeparators(d->mSettings->fileName());
    d->mBasePath = QDir::toNativeSeparators(mainConfig.absolutePath());

    qDebug() << Q_FUNC_INFO << d->mThemeCfgFile;
}

QString ThemepackLoader::wallpaper()
{
    QString rv;
    d->mSettings->beginGroup(QLatin1String("main"));
    rv = d->mSettings->value("wallpaper").toString();
    d->mSettings->endGroup();

    QDir
        prefix(QString("%1/%2/%3").arg(themePackPath).arg(d->mThemeName).arg(QLatin1String("resources")));

    return QDir::toNativeSeparators(prefix.absoluteFilePath(rv));
}

QStringList ThemepackLoader::widgets(const QString &expType)
{
    QStringList rv;
    Q_FOREACH(const QString &key, d->mSettings->childGroups()) {
        qDebug() << Q_FUNC_INFO << key;
        if (key == QLatin1String("main")) {
            continue;
        }
        d->mSettings->beginGroup(key);
        QString type = d->mSettings->value(QLatin1String("type")).toString();
        if (type != expType) {
            d->mSettings->endGroup();
            continue;
        }
        d->mSettings->endGroup();
        rv << key;
    }

    return rv;
}

QString ThemepackLoader::qmlFilesFromTheme(const QString &name)
{
    d->mSettings->beginGroup(name);
    QString fileName = d->mSettings->value("mainfile").toString();
    QString baseFolder = d->mSettings->value("basefolder").toString();
    qDebug() << Q_FUNC_INFO << name << ":" << fileName;
    d->mSettings->endGroup();

    QDir path(QString("%1/%2").arg(d->mBasePath).arg(baseFolder));
    return (QDir::toNativeSeparators(path.absoluteFilePath(fileName)));
}

QPoint ThemepackLoader::widgetPos(const QString &name)
{
    d->mSettings->beginGroup(name);
    int x = 0;
    int y = 0;

    QString x_value = d->mSettings->value("x").toString();
    QString y_value = d->mSettings->value("y").toString();
    d->mSettings->endGroup();
    QRegExp rx("^((\\d+)(|%)\\s*(-|\\+|\\*|/)\\s*(\\d+)(|%))$||^(\\d+)(|%)$");

    rx.indexIn(x_value, 0);
    x = parseValue(rx.capturedTexts(),true);

    rx.indexIn(y_value, 0);
    y = parseValue(rx.capturedTexts(),false);

    qDebug() << Q_FUNC_INFO << x << ": " << y;



    return QPoint(x, y);
}

PlexyDesk::DesktopWidget::State ThemepackLoader::widgetView(const QString &name)
{
    PlexyDesk::DesktopWidget::State default_state = PlexyDesk::DesktopWidget::NORMALSIDE;
    d->mSettings->beginGroup(name);
    QString state = d->mSettings->value("view").toString().toUpper();
    if (!state.isEmpty() && !state.isNull()) {
        if (state == "NORMALSIDE") {
           d->mSettings->endGroup(); 
           return default_state;
        } else if (state == "BACKSIDE") {
            d->mSettings->endGroup();
            return PlexyDesk::DesktopWidget::BACKSIDE;
        } else if (state == "DOCK") {
            d->mSettings->endGroup();
            return PlexyDesk::DesktopWidget::DOCK;
        }

    }

    d->mSettings->endGroup();
    return default_state;
}


void ThemepackLoader::setThemeName(const QString &name)
{
    Q_UNUSED(name);
}

int ThemepackLoader::parseValue(QStringList captured, bool calcX)
{
    QRect screenRect = QDesktopWidget().availableGeometry();
    QStringList capturedTexts = captured;
    int pValueIndex = capturedTexts.indexOf("%") - 1;
    int parsedValue1,parsedValue2;
    parsedValue1 = capturedTexts.at(pValueIndex).toUInt();//value 1 is always the percentage value provided
    int position;
    if (calcX)
        position = (screenRect.width()/100.0)*parsedValue1;
    else
        position =  (screenRect.height()/100.0)*parsedValue1;
    QRegExp rx("(-|/|\\+|\\*)");
    int operationIndex = capturedTexts.indexOf(rx);
    if (operationIndex != -1){
        int val1Index = capturedTexts.indexOf(QRegExp("(\\d+)"));
        int val2Index = capturedTexts.lastIndexOf(QRegExp("(\\d+)"));
        if (val1Index == pValueIndex)
            parsedValue2 = capturedTexts.at(val2Index).toUInt();
        else if (val2Index == pValueIndex)
            parsedValue2 = capturedTexts.at(val1Index).toUInt();
        if (capturedTexts.at(operationIndex) == "+")
            return position + parsedValue2;
        else if (capturedTexts.at(operationIndex) == "-")
            return position - parsedValue2;
        else if (capturedTexts.at(operationIndex) == "/")
            return position / parsedValue2;
        else if (capturedTexts.at(operationIndex) == "*")
            return position * parsedValue2;
    }
    return position;
}
