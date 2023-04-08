file(GLOB all_SRCS
        #####
        # ADD SOURCE FILES HERE
        #####


        main.cpp
        imgui_func.cpp
        imgui_stdlib.cpp
        imgui_style.cpp
)

add_executable(main 
    ${all_SRCS})

# include sources subfolders of app/*
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# link opengl libs
target_link_libraries(main PRIVATE glfw OpenGL::GL glad glm imgui)
