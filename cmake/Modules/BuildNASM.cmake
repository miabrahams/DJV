include(ExternalProject)

ExternalProject_Add(
    NASM
    URL http://www.nasm.us/pub/nasm/releasebuilds/2.14.02/nasm-2.14.02.tar.xz
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${CMAKE_INSTALL_PREFIX})

