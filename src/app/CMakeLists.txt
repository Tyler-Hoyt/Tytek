file(GLOB all_SRCS
        #####
        # ADD SOURCE FILES HERE
        #####


        main.cpp
        )

add_executable(${PROJECT_NAME} ${all_SRCS})

# include sources subfolders of app/*
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# link opengl libs
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL glad glm imgui)