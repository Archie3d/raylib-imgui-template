add_subdirectory(assets)

set(TARGET app)

add_executable(${TARGET})

target_sources(${TARGET}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts.h
        ${CMAKE_CURRENT_SOURCE_DIR}/event_loop.h
        ${CMAKE_CURRENT_SOURCE_DIR}/event_loop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/model.h
        ${CMAKE_CURRENT_SOURCE_DIR}/model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/controller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/controller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(${TARGET}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${TARGET}
    PRIVATE
        raylib
        imgui
        implot
        implot3d
        rlimgui
)
