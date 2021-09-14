# DTK_CORE_VERSION synchronized with git tag
# git describe --tags --abbrev=0
set(DTK_CORE_VERSION "5.5.9")

# architectureod of pc, such as x86_64-linux-gnu
set(DTK_DEB_HOST_MULTIARCH)
execute_process(COMMAND
    dpkg-architecture -qDEB_HOST_MULTIARCH
    TIMEOUT 5
    OUTPUT_VARIABLE DTK_DEB_HOST_MULTIARCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# such as dtkcore, dtkcore5, dtkcore5.5
# for example, it can be combined into libdtkcore5.5.so.5.4.3
set(DTK_VERSION_SUFFIX "")

# rewrite install prefix of target
# /use/local -> /usr/lib or /usr/include ...
string(COMPARE EQUAL "/usr/local" "${CMAKE_INSTALL_PREFIX}" dont_use_default_prefix)
if (dont_use_default_prefix)
    set(CMAKE_INSTALL_PREFIX "/usr")
endif()

option(DTK_HAS_UNIT_TEST "Control unit test generate coverage." OFF)
