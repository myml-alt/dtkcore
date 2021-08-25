cmake_minimum_required(VERSION 3.10)

include(../../cmake/config.cmake)

project(deepin-os-release VERSION ${DTK_CORE_VERSION})

set(CMAKE_CXX_STANDARD 11)
set(REQUIRED_QT_VERSION 5.11.3)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core)

include_directories(../../src)

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/../../src/dsysinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/../../src/ddesktopentry.h
)

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../src/dsysinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../src/ddesktopentry.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core)

install(
    FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/libdtk-${PROJECT_VERSION}/DCore${DTK_VERSION_SUFFIX}/bin/
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
