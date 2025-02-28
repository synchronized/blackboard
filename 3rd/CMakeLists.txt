
add_subdirectory(imgui)
add_subdirectory(ImGuizmo)

include(FetchContent)

# bgfx_cmake
FetchContent_Declare(
                     bgfx_cmake
                     GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
                     GIT_TAG master
                     GIT_SHALLOW 1
)
FetchContent_MakeAvailable(bgfx_cmake)

add_library(bgfx::bgfx ALIAS bgfx)
add_library(bgfx::bimg ALIAS bimg)
add_library(bgfx::bimg_decode ALIAS bimg_decode)
add_library(bgfx::bx ALIAS bx)