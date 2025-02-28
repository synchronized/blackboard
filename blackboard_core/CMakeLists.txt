cmake_minimum_required(VERSION 3.21)

project(blackboard_core)

file(GLOB_RECURSE SOURCES ./**.cpp ./**.c)
file(GLOB_RECURSE HEADERS ./**.hpp ./**.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
   PRIVATE
   $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
   $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${PROJECT_NAME} PRIVATE bgfx::bx bgfx::bgfx bgfx::bimg bgfx::bimg_decode)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE imguizmo::imguizmo)

target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE EnTT::EnTT)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

# compile shader
set(blackboard_shader_directory "${CMAKE_CURRENT_SOURCE_DIR}/renderer/shaders/uniform_color")
bgfx_compile_shaders(
  TYPE VERTEX
  SHADERS ${blackboard_shader_directory}/uniform_color_vs.sc
  VARYING_DEF ${blackboard_shader_directory}/varying.def.sc
  OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
  AS_HEADERS
)
bgfx_compile_shaders(
  TYPE FRAGMENT
  SHADERS ${blackboard_shader_directory}/uniform_color_fs.sc
  VARYING_DEF ${blackboard_shader_directory}/varying.def.sc
  OUTPUT_DIR ${CMAKE_BINARY_DIR}/include/generated/shaders
  AS_HEADERS
)
target_sources(
    ${PROJECT_NAME} 
    PRIVATE 
        ${blackboard_shader_directory}/uniform_color_fs.sc
        ${blackboard_shader_directory}/uniform_color_vs.sc
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/include/generated/shaders)

# target_include_directories(${PROJECT_NAME}
#                            PUBLIC
#                            ${imgui_SOURCE_SYMLINK_DIR}
#                            ${bgfx_cmake_SOURCE_DIR}/bx/inlcude
#                         #    ${SDL2_INCLUDE_DIRS}
#                         #    ${SDL2_IMAGE_INCLUDE_DIRS}
#                         #    ${SDL2_TTF_INCLUDE_DIRS}
#                         #    ${SDL2_MIXER_INCLUDE_DIRS}
# )

# if(WIN32)
# target_include_directories(${PROJECT_NAME}
#                            PUBLIC
#                            ${bgfx_cmake_SOURCE_DIR}/bx/include/compat/msvc
# )
# endif()

target_compile_definitions(${PROJECT_NAME}
                           PRIVATE
                           "-D_CRT_SECURE_NO_WARNINGS"
                           "-D__STDC_FORMAT_MACROS"
)

target_compile_definitions(${PROJECT_NAME} PUBLIC "BX_CONFIG_DEBUG=$<CONFIG:Debug>")
target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_DEFINE_MATH_OPERATORS)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)

source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${SOURCES})
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${HEADERS})
