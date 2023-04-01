#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui-filebrowser/imfilebrowser.h"

#include "function.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "Text Editor", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    ImGui::FileBrowser fileDialog;

    fileDialog.SetTitle("title");
    //fileDialog.SetTypeFilters({".txt"});
    
    // Set up ImGui
    ImGuiInit();

    static char str_hold[2048] = ""; //make a string
    std::filesystem::__cxx11::path lastSelectedFile;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
           
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if(ImGui::GetIO().WantCaptureMouse) {
                    break;
                }
            }
        }

        // Widgets from here ----
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::SetNextWindowSize(ImVec2(2560, 1440));
        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::Begin("Tyler's Text Editor", NULL,
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_MenuBar);

        fileDialog.Display();
        if(fileDialog.HasSelected()) {
            // Clear the Window
            strncpy(str_hold, "", 2048); 
            std::ifstream istream;
            istream.open(fileDialog.GetSelected().string());
            if(!istream) {
                std::cout << "Opening file failed!" << std::endl;
            }
            char c;
            for(std::string line; std::getline(istream, line);) {
                strncat(str_hold, line.c_str(), line.size());
                strcat(str_hold, "\n");
            }
            istream.close();
            lastSelectedFile = fileDialog.GetSelected();
            fileDialog.ClearSelected();
        }
        // ImGui Window
        if(ImGui::BeginMenuBar()) {
            if(ImGui::BeginMenu("File")) {
                if(ImGui::MenuItem("Open")) {
                    fileDialog.Open();
                }
                if(ImGui::MenuItem("Save")) {
                    std::ofstream ostream;
                    ostream.open(lastSelectedFile.string());
                    if(!ostream) {
                        std::cout << "Opening file failed!" << std::endl;
                    }
                    ostream.write((char * )str_hold, 2048);
                    ostream.close();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::InputTextMultiline("", str_hold, 2048, ImVec2(2510, 1260)); 
        //
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        // Widgets to here ----

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
