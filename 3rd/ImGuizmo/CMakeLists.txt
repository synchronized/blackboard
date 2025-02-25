project(imguizmo)

add_library(${PROJECT_NAME} STATIC "")
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
        GraphEditor.cpp
        ImCurveEdit.cpp
        ImGradient.cpp
        ImGuizmo.cpp
        ImSequencer.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)