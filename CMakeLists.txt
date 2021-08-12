# cmake CMakeLists.txt && make -j$(nproc) && sudo make install
cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/cmake.conf)

add_subdirectory(src)
add_subdirectory(tools/settings)
add_subdirectory(tools/deepin-os-release)

add_custom_target(check)
add_custom_command(TARGET check
    COMMAND cd ${CMAKE_CURRENT_LIST_DIR}/tests && qmake -o ${CMAKE_CURRENT_LIST_DIR}/tests/Makefile ${CMAKE_CURRENT_LIST_DIR}/tests/tests.pro LIBS+=-L${CMAKE_CURRENT_LIST_DIR}/obj-${DTK_DEB_HOST_MULTIARCH}/src
    COMMAND cd ${CMAKE_CURRENT_LIST_DIR}/tests && export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${CMAKE_CURRENT_LIST_DIR}/obj-${DTK_DEB_HOST_MULTIARCH}/src && make check
)
add_dependencies(check dtkcore${DTK_VERSION_SUFFIX})

install(
    FILES
    ${CMAKE_CURRENT_LIST_DIR}/tools/script/dtk-translate.py
    ${CMAKE_CURRENT_LIST_DIR}/tools/script/dtk-license.py

    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/libdtk-${DTK_CORE_VERSION}/DCore/bin/
    PERMISSIONS WORLD_EXECUTE
)

# pkg-config --libs --cflags dtkcore5.5
# ldconfig --verbose | grep dtk
# pkg-config --list-all | grep dtkcore

# dpkg -L libdtkcore5.5-dev

# uninstall list:
# rm -rf /usr/include/libdtk-5.5.5
# rm -f /usr/lib/x86_64-linux-gnu/libdtkcore5.5.so
# rm -f /usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dtkcore5.5.pri
# rm -f /usr/lib/x86_64-linux-gnu/pkgconfig/dtkcore5.5.pc
# rm -f /usr/lib/x86_64-linux-gnu/cmake/DtkTools5.5/DtkTools5.5Config.cmake
# rm -f /usr/lib/x86_64-linux-gnu/cmake/DtkTools5.5/DtkSettingsToolsMacros5.5.cmake
# rm -f /usr/lib/x86_64-linux-gnu/cmake/DtkCore5.5/DtkCore5.5Config.cmake
# rm -f /usr/lib/x86_64-linux-gnu/cmake/DtkCMake5.5/DtkCMake5.5Config.cmake

