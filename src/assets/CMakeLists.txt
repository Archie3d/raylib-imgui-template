
bin2h(
    SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/DMSans-Regular.ttf"
    HEADER_FILE "${CMAKE_CURRENT_BINARY_DIR}/DMSans-Regular-ttf.h"
    VARIABLE_NAME "DMSANS_REGULAR_TTF"
    HEADER_NAMESPACE "assets"
)

bin2h(
    SOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/forkawesome-webfont.ttf"
    HEADER_FILE "${CMAKE_CURRENT_BINARY_DIR}/forkawesome-webfont-ttf.h"
    VARIABLE_NAME "FORKAWESOME_WEBFONT_TTF"
    HEADER_NAMESPACE "assets"
)

add_library(assets INTERFACE)
target_include_directories(assets
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)
