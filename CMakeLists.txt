cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# By default, MSVC uses the GBK encoding.
# To use UTF-8 without a BOM header,
#     you need to add the following statement.
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#include(cmake/fetch_external_dependencies.cmake)


set(PROJECT_NAME blackboard)
project (${PROJECT_NAME})

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

include_directories(${PROJECT_SOURCE_DIR})

#assimp provides CMake targets:

  # this is heuristically generated, and may not be correct
  find_package(assimp CONFIG REQUIRED)
  # target_link_libraries(main PRIVATE assimp::assimp)

#bgfx provides CMake targets:

  # this is heuristically generated, and may not be correct
  find_package(bgfx CONFIG REQUIRED)
  # note: 1 additional targets are not displayed.
  # target_link_libraries(main PRIVATE bgfx::bx bgfx::bgfx bgfx::bimg bgfx::bimg_decode)

#entt provides CMake targets:

  find_package(EnTT CONFIG REQUIRED)
  # target_link_libraries(main PRIVATE EnTT::EnTT)

#The package glm provides CMake targets:

  find_package(glm CONFIG REQUIRED)
  # target_link_libraries(main PRIVATE glm::glm)

#sdl2 provides CMake targets:

  find_package(SDL2 CONFIG REQUIRED)
  # target_link_libraries(main
  #     PRIVATE
  #     $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  #     $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
  # )

#sdl2-ttf provides CMake targets:

  find_package(SDL2_ttf CONFIG REQUIRED)
  # target_link_libraries(main PRIVATE $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)

# The package spdlog provides CMake targets:

  find_package(spdlog CONFIG REQUIRED)
  # target_link_libraries(main PRIVATE spdlog::spdlog)

# stduuid provides CMake targets:

  # this is heuristically generated, and may not be correct
  find_package(stduuid CONFIG REQUIRED)
  # target_link_libraries(main PRIVATE stduuid)

add_subdirectory(3rd)
add_subdirectory(blackboard_editor)
add_subdirectory(blackboard_core)
