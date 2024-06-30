cmake_minimum_required(VERSION 3.5)

project(Mykhailenko_Test VERSION 0.1 LANGUAGES CXX)
set(PROJECT_NAME Mykhailenko_Test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/models
    ${CMAKE_SOURCE_DIR}/include/delegates
    ${CMAKE_SOURCE_DIR}/include/data
    ${CMAKE_SOURCE_DIR}/include/items
)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/models/treemodel.cpp
    src/delegates/icondelegate.cpp
    src/data/sqlitestorage.cpp
    src/items/treeitem.cpp
    src/items/countryitem.cpp
    src/items/operatoritem.cpp
    src/mainwindow.ui
)

set(PROJECT_HEADERS
    include/mainwindow.h
    include/models/treemodel.h
    include/delegates/icondelegate.h
    include/data/sqlitestorage.h
    include/data/storage.h
    include/items/treeitem.h
    include/items/countryitem.h
    include/items/operatoritem.h
    include/items/entities.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

set(ICONS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources/Icons")
file(GLOB ICON_FILES "${ICONS_SOURCE_DIR}/*.png")

qt_add_resources(${PROJECT_NAME} "icons"
    PREFIX "/Icons"
    BASE "${ICONS_SOURCE_DIR}"
    FILES ${ICON_FILES}
)

set(DATA_SOURCE_DIR "${CMAKE_SOURCE_DIR}/resources/data")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${DATA_SOURCE_DIR}/system.db"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/system.db"

    COMMAND "${CMAKE_COMMAND}" -E
        env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE:${PROJECT_NAME}>"
    COMMENT "Copying database to build directory and running windeployqt"
)
