# 1. 该文件需要包含在 CMakeLists.txt 文件的最前面，project 的后面
# 2. 这里的宏定义、以来库主要用于 src 目录下生成 libdtkcore 动态库
# 3. 另外保证项目内部的单元测试、示例程序等可以方便的包含使用这些内容
# 4. 关于静态库的使用：对于使用 libdtkcore.a 的目标程序来说，需要
#   添加以下所有的库链接到目标程序。如果以下库的静态版本已被链接进
#   libdtkcore.a，则不需要再额外添加。

# 5. 切记：和 libdtkcore.so 无关的库、宏定义一定不能放在这里！！！
#   要在各自的项目中单独添加。

set(REQUIRED_QT_VERSION 5.11.3)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTOMOC_COMPILER_PREDEFINES ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-pipe -O2 -std=gnu++11 -Wall -Wextra -D_REENTRANT")

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED COMPONENTS Core DBus Xml Concurrent)
find_library(QGSETTINGS_LIB gsettings-qt)

# for coverage
if (DTK_HAS_UNIT_TEST)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov --coverage")
endif()

set(DTKCORE_COMMON_LIBS
    Qt5::Core
    Qt5::DBus
    Qt5::Xml
    Qt5::Concurrent
    ${QGSETTINGS_LIB}
    -lpthread
)

add_definitions(
    -DQT_MESSAGELOGCONTEXT
    -DLIBDTKCORE_LIBRARY
    -DDTK_LIB_DIR_NAME=\"libdtk-${PROJECT_VERSION}\"
    -DDCORE_TRANSLATIONS_PATH=\"/usr/share/libdtk-${PROJECT_VERSION}/DCore${DTK_VERSION_SUFFIX}/translations\"
    -DDCORE_TRANSLATIONS_DIR=\"libdtk-${PROJECT_VERSION}/DCore${DTK_VERSION_SUFFIX}/translations\"
    -DLIBDTKCORE_LIBRARY
    -DQT_NO_DEBUG
    # -DQT_NO_KEYWORDS
    -DQT_DBUS_LIB
    -DQT_XML_LIB
    -DQT_CORE_LIB
)
