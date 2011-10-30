SET(sourceFiles
    friend.cpp
    friendlist.cpp
    )

SET(headerFiles
    plugin.h
    friend.h
    friendlist.h
    )

QT4_WRAP_CPP(QT_MOC_SRCS ${headerFiles})

SET(sourceFiles
    ${QTMOC_SRCS}
    ${sourceFiles}
    ${headerFiles}
    )

SET(libs
    ${PLEXY_CORE_LIBRARY}
    ${QT_QTSCRIPT_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}
    )

ADD_LIBRARY(friendlistmodel  SHARED ${sourceFiles} ${QT_MOC_SRCS})

IF(MINGW)
    SET_TARGET_PROPERTIES(friendlistmodel PROPERTIES
        IMPORT_SUFFIX ".lib"
        IMPORT_PREFIX ""
        PREFIX ""
        )
ENDIF(MINGW)

TARGET_LINK_LIBRARIES(friendlistmodel
    ${libs}
    )

# Note QT_IMPORTS_INSTALL_DIR is relative and handled in the main CMakeLists.txt file
INSTALL(TARGETS friendlistmodel DESTINATION ${CMAKE_INSTALL_LIBDIR})
INSTALL(TARGETS friendlistmodel DESTINATION ${QT_IMPORTS_INSTALL_DIR}/PlexyDesk/Facebook/FriendListModel)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/qmldir  DESTINATION ${QT_IMPORTS_INSTALL_DIR}/PlexyDesk/Facebook/FriendListModel)
