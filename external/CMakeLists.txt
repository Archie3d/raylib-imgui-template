include(FetchContent)
include(ExternalProject)

##
## RayLib
##
set(RAYLIB_VERSION 6.0)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_GetProperties(raylib)
if(NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
endif()

##
## ImGui
##
set(IMGUI_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

set(IMGUI_SRC
    ${IMGUI_SRC_DIR}/imgui.cpp
    ${IMGUI_SRC_DIR}/imgui_draw.cpp
    ${IMGUI_SRC_DIR}/imgui_tables.cpp
    ${IMGUI_SRC_DIR}/imgui_widgets.cpp
    ${IMGUI_SRC_DIR}/misc/cpp/imgui_stdlib.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})

target_include_directories(imgui PUBLIC
    ${IMGUI_SRC_DIR}
    ${IMGUI_SRC_DIR}/backends
)

##
## implot
##
set(IMPLOT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/implot)

set(IMPLOT_SRC
    ${IMPLOT_SRC_DIR}/implot.h
    ${IMPLOT_SRC_DIR}/implot.cpp
    ${IMPLOT_SRC_DIR}/implot_items.cpp
    ${IMPLOT_SRC_DIR}/implot_internal.h
)
add_library(implot STATIC ${IMPLOT_SRC})

target_include_directories(implot PUBLIC
    ${IMPLOT_SRC_DIR}
)

target_link_libraries(implot PUBLIC
    imgui
)

##
## implot3d
##
set(IMPLOT3D_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/implot3d)

set(IMPLOT3D_SRC
    ${IMPLOT3D_SRC_DIR}/implot3d.h
    ${IMPLOT3D_SRC_DIR}/implot3d.cpp
    ${IMPLOT3D_SRC_DIR}/implot3d_items.cpp
    ${IMPLOT3D_SRC_DIR}/implot3d_meshes.cpp
    ${IMPLOT3D_SRC_DIR}/implot3d_internal.h
)

add_library(implot3d STATIC ${IMPLOT3D_SRC})

target_include_directories(implot3d PUBLIC
    ${IMPLOT3D_SRC_DIR}
)

target_link_libraries(implot3d PUBLIC
    imgui
)

##
## rlImGui
##
set(RLIMGUI_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rlImGui)

set(RLIMGUI_SRC
    ${RLIMGUI_SRC_DIR}/rlImGui.h
    ${RLIMGUI_SRC_DIR}/rlImGui.cpp
    ${RLIMGUI_SRC_DIR}/rlImGuiColors.h
    ${RLIMGUI_SRC_DIR}/imgui_impl_raylib.h
    ${RLIMGUI_SRC_DIR}/extras/FA6FreeSolidFontData.h
    ${RLIMGUI_SRC_DIR}/extras/IconsFontAwesome6.h
)

add_library(rlimgui STATIC ${RLIMGUI_SRC})

target_include_directories(rlimgui PUBLIC
    ${RLIMGUI_SRC_DIR}
)

target_link_libraries(rlimgui PUBLIC
    imgui
    raylib
)
