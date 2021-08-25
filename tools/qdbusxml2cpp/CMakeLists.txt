cmake_minimum_required(VERSION 3.10)

include(../../cmake/config.cmake)

project(qdbusxml2cpp-fix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(REQUIRED_QT_VERSION 5.11.3)

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core DBus)

include_directories(../../src)

add_executable(${PROJECT_NAME} qdbusxml2cpp.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::DBus Qt5::DBusPrivate)

install(
    FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
