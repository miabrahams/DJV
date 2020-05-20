include(ExternalProject)

ExternalProject_Add(
    FreeType
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/FreeType
    DEPENDS ZLIB
    URL http://download.savannah.gnu.org/releases/freetype/freetype-2.10.2.tar.gz
    CMAKE_ARGS
        -DCMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_INSTALL_LIBDIR=lib
        -DCMAKE_PREFIX_PATH=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
        -DZLIB_SHARED_LIBS=${ZLIB_SHARED_LIBS}
        -DFT_WITH_ZLIB=ON
        -DCMAKE_DISABLE_FIND_PACKAGE_BZip2=TRUE
        -DCMAKE_DISABLE_FIND_PACKAGE_PNG=TRUE
        -DCMAKE_DISABLE_FIND_PACKAGE_HarfBuzz=TRUE
        -DCMAKE_DISABLE_FIND_PACKAGE_BrotliDec=TRUE)
