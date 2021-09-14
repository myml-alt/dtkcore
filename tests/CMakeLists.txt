cmake_minimum_required(VERSION 3.13)

include(../cmake/config.cmake)

project(unit-tests LANGUAGES CXX)

set(DTK_HAS_UNIT_TEST ON)
include(../cmake/dtkcore_common.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Test)

include_directories(
    # sources dir
    ../src
    ../src/base
    ../src/base/private
    ../src/filesystem
    ../src/log
    ../src/settings
    ../src/util
)

# for asan
if (NOT ${CMAKE_SYSTEM_PROCESSOR} MATCHES "mips64")
    set(BUILD_WITH_ASAN)
    set(CMAKE_CXX_FLAGS
        "-g -Wall -fsanitize=address -fsanitize-recover=address"
    )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--export-dynamic -O2 -fno-access-control")

add_definitions(-DOS_VERSION_TEST_FILE=\"/tmp/etc/os-version\")

add_executable(${PROJECT_NAME}
    main.cpp

    data.qrc

    ut_dutil.h
    ut_singleton.h

    ut_dutil.cpp
    ut_singleton.cpp
    ut_dvtablehook.cpp
    ut_dthreadutils.cpp
    ut_ddesktopentrytest.cpp


    ut_ddisksizeformatter.cpp
    ut_dfilesystemwatcher.cpp
    ut_dfilewatcher.cpp
    ut_dfilewatchermanager.cpp
    ut_dpathbuf.cpp
    ut_dpinyin.cpp
    ut_drecentmanager.cpp
    ut_dsecurestring.cpp
    ut_dsettings.cpp
    ut_dstandardpaths.cpp
    ut_dtimeunitformatter.cpp
    ut_dtrashmanager.cpp
    ut_gsettingsbackend.cpp
    ut_logger.cpp
    ut_qsettingsbackend.cpp
)

if (NOT DEFINED ENV{DCORE_BUILD_LIB_PATH})
    find_package(DtkCore${DTK_VERSION_SUFFIX} REQUIRED dtkcore${DTK_VERSION_SUFFIX})
    set(DTKCORE_LIB ${DtkCore${DTK_VERSION_SUFFIX}_LIBRARIES})
else()
    set(DTKCORE_LIB "-L$ENV{DCORE_BUILD_LIB_PATH} -ldtkcore${DTK_VERSION_SUFFIX}")
endif()

target_link_libraries(${PROJECT_NAME}
    Qt5::Test
    ${DTKCORE_LIB}
    ${DTKCORE_COMMON_LIBS}
    -L/usr/lib/${DTK_DEB_HOST_MULTIARCH} -lgtest -ldl
)

add_custom_target(check)
add_custom_command(TARGET check
    COMMAND export ASAN_OPTIONS=halt_on_error=0 && export LD_LIBRARY_PATH=$ENV{DCORE_BUILD_LIB_PATH}:$LD_LIBRARY_PATH && ./${PROJECT_NAME}
)
add_dependencies(check ${PROJECT_NAME})
