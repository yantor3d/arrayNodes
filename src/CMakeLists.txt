set(SOURCE_FILES
    "n_chain.h"
    "n_clamp.h"
    "n_ctor.h"
    "n_iter.h"
    "n_modify.h"
    "n_multi.h"
    "n_normalize.h"
    "n_reduce.h"
    "n_remap.h"
    "n_scalar.h"
    "n_slice.h"
    "utils.h"
    "n_chain.cpp"
    "n_clamp.cpp"
    "n_ctor.cpp"
    "n_iter.cpp"
    "n_modify.cpp"
    "n_multi.cpp"
    "n_normalize.cpp"
    "n_reduce.cpp"
    "n_remap.cpp"
    "n_scalar.cpp"
    "n_slice.cpp"
    "pluginMain.cpp"
    "utils.cpp"
)

find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${PROJECT_NAME})