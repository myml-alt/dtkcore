cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/cmake.conf)

project(dtk-settings VERSION ${DTK_CORE_VERSION})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(REQUIRED_QT_VERSION 5.11.3)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core Xml)
find_library(QGSETTINGS_LIB gsettings-qt)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../src)
set(HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/../../src/settings/dsettings.h
        ${CMAKE_CURRENT_LIST_DIR}/../../src/settings/dsettingsgroup.h
        ${CMAKE_CURRENT_LIST_DIR}/../../src/settings/dsettingsoption.h
        ${CMAKE_CURRENT_LIST_DIR}/../../src/settings/dsettingsbackend.h
)
set(SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/../../src/settings/dsettings.cpp
        ${CMAKE_CURRENT_LIST_DIR}/../../src/settings/dsettingsgroup.cpp
        ${CMAKE_CURRENT_LIST_DIR}/../../src/settings/dsettingsoption.cpp
)

qt5_wrap_cpp(${PROJECT_NAME}
        dsettings.cpp
        dsettingsoption.cpp
        dsettingsgroup.cpp
        dsettingsbackend.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Xml  ${QGSETTINGS_LIB})

install(
    FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/libdtk-${PROJECT_VERSION}/DCore${DTK_VERSION_SUFFIX}/bin/
    PERMISSIONS WORLD_EXECUTE
)
