cmake_minimum_required(VERSION 3.10)

include(cmake/config.cmake)

set(ENV{DCORE_BUILD_LIB_PATH}
    ${CMAKE_BINARY_DIR}/src
)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(tools/settings)
add_subdirectory(tools/deepin-os-release)

add_dependencies(unit-tests dtkcore${DTK_VERSION_SUFFIX})

install(
    FILES
    ${CMAKE_CURRENT_LIST_DIR}/tools/script/dtk-translate.py
    ${CMAKE_CURRENT_LIST_DIR}/tools/script/dtk-license.py

    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${DTK_DEB_HOST_MULTIARCH}/libdtk-${DTK_CORE_VERSION}/DCore/bin/
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

