 TARGET  = qmlfolderlistmodelplugin
 TARGETPATH = Qt/labs/folderlistmodel

 QT += declarative script

 SOURCES += qdeclarativefolderlistmodel.cpp plugin.cpp iconloader.cpp
 HEADERS += qdeclarativefolderlistmodel.h iconloader.h

 QTDIR_build:DESTDIR = $$QT_BUILD_TREE/imports/$$TARGETPATH
 target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

 qmldir.files += $$PWD/qmldir
 qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

 symbian:{
     TARGET.UID3 = 0x20021320

     isEmpty(DESTDIR):importFiles.sources = qmlfolderlistmodelplugin$${QT_LIBINFIX}.dll qmldir
     else:importFiles.sources = $$DESTDIR/qmlfolderlistmodelplugin$${QT_LIBINFIX}.dll qmldir
     importFiles.path = $$QT_IMPORTS_BASE_DIR/$$TARGETPATH

     DEPLOYMENT = importFiles
 }

 INSTALLS += target qmldir

OTHER_FILES += \
    components/Icon.qml \
    desktopview.qml
