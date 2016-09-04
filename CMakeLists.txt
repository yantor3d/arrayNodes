cmake_minimum_required(VERSION 2.6)
project(arrayNodes)

set(MAYA_LIBRARIES OpenMaya OpenMayaAnim OpenMayaFX OpenMayaRender OpenMayaUI Foundation)

INCLUDE_DIRECTORIES($ENV{MAYA_INCLUDE_PATH})
LINK_DIRECTORIES($ENV{MAYA_LIBRARY_PATH})

set(SOURCE_FILES
    "src/n_chain.h"
    "src/n_clamp.h"
    "src/n_ctor.h"
    "src/n_iter.h"
    "src/n_modify.h"
    "src/n_multi.h"
    "src/n_normalize.h"
    "src/n_reduce.h"
    "src/n_remap.h"
    "src/n_scalar.h"
    "src/n_slice.h"
    "src/utils.h"
    "src/n_chain.cpp"
    "src/n_clamp.cpp"
    "src/n_ctor.cpp"
    "src/n_iter.cpp"
    "src/n_modify.cpp"
    "src/n_multi.cpp"
    "src/n_normalize.cpp"
    "src/n_reduce.cpp"
    "src/n_remap.cpp"
    "src/n_scalar.cpp"
    "src/n_slice.cpp"
    "src/pluginMain.cpp"
    "src/utils.cpp"
)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${MAYA_LIBRARIES})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES 
    COMPILE_DEFINITIONS "EQUIRE_IOSTREAM;_BOOL;NT_PLUGIN"
    LINK_FLAGS "/export:initializePlugin /export:uninitializePlugin"
    PREFIX ""
    SUFFIX ".mll"
)