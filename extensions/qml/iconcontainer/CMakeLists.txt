INCLUDE (${QT_USE_FILE})
INCLUDE_DIRECTORIES(
   ${QT_INCLUDES}
   
   
)

SET(sourceFiles
	plugin.cpp
	qdeclarativefolderlistmodel.cpp
	iconloader.cpp
)

SET(headerFiles
	qdeclarativefolderlistmodel.h
        iconloader.h
)

SET(QTMOC_SRCS
	qdeclarativefolderlistmodel.h
        iconloader.h
)
qt4_wrap_cpp(QT_MOC_SRCS ${QTMOC_SRCS})

SET(sourceFiles
   ${QTMOC_SRCS}
   ${sourceFiles}
   ${headerFiles}
)

SET(libs
   ${PLEXY_CORE_LIBRARY}
)

add_library (iconcontainer ${sourceFiles} ${QT_MOC_SRCS})
#IF(MINGW)
#    SET_TARGET_PROPERTIES(desktopview PROPERTIES
#        IMPORT_SUFFIX ".lib"
#        IMPORT_PREFIX ""
#        PREFIX ""
#    )
#ENDIF(MINGW)

TARGET_LINK_LIBRARIES(
   iconcontainer
   ${libs}
)
FILE( GLOB QMLFILES *.qml)
INSTALL (FILES ${QMLFILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/plexyext/)
INSTALL (TARGETS iconcontainer DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/plexyext/)
ADD_SUBDIRECTORY(component)


