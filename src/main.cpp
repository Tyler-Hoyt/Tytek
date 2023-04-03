#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui-filebrowser/imfilebrowser.h"

#include "function.h"

#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "Text Editor", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    ImGui::FileBrowser fileDialog;
    fileDialog.SetWindowSize(1000, 1000);

    fileDialog.SetTitle("File Browser");
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

        ImGuiWidgets(lastSelectedFile, str_hold, fileDialog);
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
