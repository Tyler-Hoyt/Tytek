#include "function.h" 

void ImGuiInit() {
    // Font and Size of Gui SFML is bad with this
    ImGui::GetIO().FontGlobalScale = 3.f;
    ImGui::GetStyle().ScaleAllSizes(3.f);
}
