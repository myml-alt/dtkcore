cmake_minimum_required(VERSION 3.10)

include(../cmake/config.cmake)

project(dtkcore${DTK_VERSION_SUFFIX} VERSION ${DTK_CORE_VERSION} LANGUAGES CXX)

include(../cmake/dtkcore_common.cmake)

# Qt >= 5.11.3
set(REQUIRED_QT_VERSION 5.11.3)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(-DQT_NO_KEYWORDS)

if (DTK_HAS_UNIT_TEST)
    set(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
    set(GCC_COVERAGE_LINK_FLAGS "-lgcov")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

include_directories(base filesystem log settings util)

set(D_HEADERS
    DSysInfo

    log/DLog

    base/DObject
    base/DObjectPrivate
    base/DSingleton

    filesystem/DFileWatcher
    filesystem/DBaseFileWatcher
    filesystem/DFileSystemWatcher
    filesystem/DFileWatcherManager
    filesystem/DPathBuf
    filesystem/DStandardPaths
    filesystem/DTrashManager

    settings/DSettings
    settings/DSettingsGroup
    settings/DSettingsOption

    util/DUtil
    util/DPinyin
    util/DDBusSender
    util/DRecentManager
    util/DNotifySender
    util/DExportedInterface
    util/DVtableHook
    util/DFileServices
    util/DThreadUtils
)

# generate dtkcore_config.h version info from project version info
if (NOT PROJECT_VERSION_PATCH)
    set(PROJECT_VERSION_PATCH 0)
endif()

if (NOT PROJECT_VERSION_TWEAK)
    set(PROJECT_VERSION_TWEAK 0)
endif()

set(DTK_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(DTK_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(DTK_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(DTK_VERSION_BUILD "${PROJECT_VERSION_TWEAK}")
set(DTK_VERSION_STR   "${PROJECT_VERSION}")

file(WRITE  ${CMAKE_CURRENT_LIST_DIR}/dtkcore_config.h "#define DTK_VERSION_MAJOR ${DTK_VERSION_MAJOR}\n")
file(APPEND ${CMAKE_CURRENT_LIST_DIR}/dtkcore_config.h "#define DTK_VERSION_MINOR ${DTK_VERSION_MINOR}\n")
file(APPEND ${CMAKE_CURRENT_LIST_DIR}/dtkcore_config.h "#define DTK_VERSION_PATCH ${DTK_VERSION_PATCH}\n")
file(APPEND ${CMAKE_CURRENT_LIST_DIR}/dtkcore_config.h "#define DTK_VERSION_BUILD ${DTK_VERSION_BUILD}\n")
file(APPEND ${CMAKE_CURRENT_LIST_DIR}/dtkcore_config.h "#define DTK_VERSION_STR \"${DTK_VERSION_STR}\"\n\n")

# generate dtkcore_config.h defined info from Dxxx headers
string(REGEX MATCHALL "D[a-zA-Z0-9]+" FILE_BASENAME "${D_HEADERS}")

foreach(D_HEADERS_DEFINED ${FILE_BASENAME})
    file(APPEND ${CMAKE_CURRENT_LIST_DIR}/dtkcore_config.h "#define DTKCORE_CLASS_${D_HEADERS_DEFINED}\n")
endforeach()

set(PUBLIC_HEADERS
    dtkcore_global.h
    dtkcore_config.h
    dsysinfo.h
    dsecurestring.h
    ddesktopentry.h

    base/dobject.h
    base/dsingleton.h

    filesystem/dbasefilewatcher.h
    filesystem/dfilesystemwatcher.h
    filesystem/dfilewatcher.h
    filesystem/dfilewatchermanager.h
    filesystem/dpathbuf.h
    filesystem/dstandardpaths.h
    filesystem/dtrashmanager.h

    log/RollingFileAppender.h
    log/Logger.h
    log/FileAppender.h
    log/CuteLogger_global.h
    log/ConsoleAppender.h
    log/AbstractStringAppender.h
    log/AbstractAppender.h
    log/LogManager.h

    settings/backend/qsettingbackend.h
    settings/dsettings.h
    settings/dsettingsoption.h
    settings/dsettingsgroup.h
    settings/dsettingsbackend.h

    util/dutil.h
    util/dpinyin.h
    util/dtimeunitformatter.h
    util/dabstractunitformatter.h
    util/ddisksizeformatter.h
    util/ddbussender.h
    util/drecentmanager.h
    util/dnotifysender.h
    util/dexportedinterface.h
    util/dvtablehook.h
    util/dfileservices.h
    util/dthreadutils.h
)

set(PRIVATE_HEADERS
    base/private/dobject_p.h
    filesystem/private/dfilesystemwatcher_linux_p.h
    filesystem/private/dbasefilewatcher_p.h
)

# generate DtkCores from PUBLIC_HEADERS
file(WRITE  ${CMAKE_CURRENT_LIST_DIR}/DtkCores "#ifndef DTK_CORE_MODULE_H\n#define DTK_CORE_MODULE_H\n")
string(REGEX MATCHALL "[a-zA-Z0-9_]+.h" PUB_HEADERS_BASENAME "${PUBLIC_HEADERS}")
foreach(PUB_HEADER ${PUB_HEADERS_BASENAME})
    file(APPEND ${CMAKE_CURRENT_LIST_DIR}/DtkCores "#include \"${PUB_HEADER}\"\n")
endforeach()
file(APPEND  ${CMAKE_CURRENT_LIST_DIR}/DtkCores "#endif")

set(HEADERS
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
)

set(SOURCES
    dsysinfo.cpp
    dsecurestring.cpp
    ddesktopentry.cpp
    # TODO
    # dtkcore_global.cpp

    base/dobject.cpp

    filesystem/dbasefilewatcher.cpp
    filesystem/dfilewatcher.cpp
    filesystem/dfilewatchermanager.cpp
    filesystem/dstandardpaths.cpp
    filesystem/dpathbuf.cpp
    # TODO: linux/win
    filesystem/dfilesystemwatcher_linux.cpp
    filesystem/dtrashmanager_linux.cpp

    log/RollingFileAppender.cpp
    log/Logger.cpp
    log/FileAppender.cpp
    log/ConsoleAppender.cpp
    log/AbstractStringAppender.cpp
    log/AbstractAppender.cpp
    log/LogManager.cpp

    settings/backend/gsettingsbackend.cpp
    settings/backend/qsettingbackend.cpp
    settings/dsettings.cpp
    settings/dsettingsoption.cpp
    settings/dsettingsgroup.cpp

    util/dtimeunitformatter.cpp
    util/dabstractunitformatter.cpp
    util/ddisksizeformatter.cpp
    util/ddbussender.cpp
    util/drecentmanager.cpp
    util/dnotifysender.cpp
    util/dpinyin.cpp
    util/dexportedinterface.cpp
    util/dvtablehook.cpp
    util/dthreadutils.cpp
    util/dfileservices_linux.cpp
)

qt5_wrap_cpp(${PROJECT_NAME}
    ddesktopentry.cpp

    # util
    dexportedinterface.cpp
    dthreadutils.cpp

    # filesystem
    dfilewatchermanager.cpp

    # settings/backend
    gsettingsbackend.cpp
    qsettingbackend.cpp

    # settings
    dsettings.cpp
    dsettingsoption.cpp
    dsettingsgroup.cpp
    dsettingsbackend.cpp
)

set(RESOURCES
    util/util.qrc
)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
if (BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES} ${RESOURCES})
else()
    add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES} ${RESOURCES})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${DTKCORE_COMMON_LIBS} ${QGSETTINGS_LIB} ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})

set(INSTALL_HEADERS
    ${HEADERS}
    ${D_HEADERS}
    DtkCores
)

# 库文件安装路径
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib/${DTK_DEB_HOST_MULTIARCH}
    ARCHIVE DESTINATION lib/${DTK_DEB_HOST_MULTIARCH}
)

# 头文件安装路径
install(FILES ${INSTALL_HEADERS}
    DESTINATION include/libdtk-${PROJECT_VERSION}/DCore${DTK_VERSION_SUFFIX}
)

# generate and install pkgconfig file
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/../cmake/DtkCore${DTK_VERSION_SUFFIX}/dtkcore${DTK_VERSION_SUFFIX}.pc.in
    ${CMAKE_BINARY_DIR}/cmake/DtkCore${DTK_VERSION_SUFFIX}/dtkcore${DTK_VERSION_SUFFIX}.pc @ONLY
)
install(
    FILES ${CMAKE_BINARY_DIR}/cmake/DtkCore${DTK_VERSION_SUFFIX}/dtkcore${DTK_VERSION_SUFFIX}.pc
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/pkgconfig
)

# generate and install qt_lib_dtkcore5.5.pri
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/../cmake/DtkCore${DTK_VERSION_SUFFIX}/qt_lib_dtkcore${DTK_VERSION_SUFFIX}.pri.in
    ${CMAKE_BINARY_DIR}/cmake/DtkCore${DTK_VERSION_SUFFIX}/qt_lib_dtkcore${DTK_VERSION_SUFFIX}.pri @ONLY
)
install(
    FILES ${CMAKE_BINARY_DIR}/cmake/DtkCore${DTK_VERSION_SUFFIX}/qt_lib_dtkcore${DTK_VERSION_SUFFIX}.pri
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/qt5/mkspecs/modules
)

# generate and install DtkCore5.5Config.cmake
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/../cmake/DtkCore${DTK_VERSION_SUFFIX}/DtkCore${DTK_VERSION_SUFFIX}Config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/DtkCore${DTK_VERSION_SUFFIX}/DtkCore${DTK_VERSION_SUFFIX}Config.cmake @ONLY
)
install(FILES ${CMAKE_BINARY_DIR}/cmake/DtkCore${DTK_VERSION_SUFFIX}/DtkCore${DTK_VERSION_SUFFIX}Config.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/cmake/DtkCore${DTK_VERSION_SUFFIX}
)

# install DtkTools5.5 cmake to /usr/lib/x86_64-linux-gnu/cmake/Dtk[Core|CMake|Tools]
install(FILES ${CMAKE_CURRENT_LIST_DIR}/../cmake/DtkCMake${DTK_VERSION_SUFFIX}/DtkCMake${DTK_VERSION_SUFFIX}Config.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/cmake/DtkCMake${DTK_VERSION_SUFFIX}
)

install(FILES ${CMAKE_CURRENT_LIST_DIR}/../cmake/DtkTools${DTK_VERSION_SUFFIX}/DtkTools${DTK_VERSION_SUFFIX}Config.cmake
    ${CMAKE_CURRENT_LIST_DIR}/../cmake/DtkTools${DTK_VERSION_SUFFIX}/DtkSettingsToolsMacros${DTK_VERSION_SUFFIX}.cmake
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/cmake/DtkTools${DTK_VERSION_SUFFIX}
)

