file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

add_executable(${PROJECT_NAME} ${all_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL glad glm imgui)
