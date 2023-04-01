add_executable(main 
    main.cpp
    ImGuiFunc.cpp
)

target_link_libraries(main PRIVATE sfml-graphics)
target_link_libraries(main PRIVATE ImGui-SFML::ImGui-SFML)
