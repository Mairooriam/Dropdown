#include "ImguiManager.h"

int main(int argc, char const *argv[])
{
    ImguiManager imgui;
    if (!imgui.initialize()) {
        return 1;
    }

    while (!imgui.ShouldClose()) {
        imgui.PollEvents();
        imgui.Begin();
        imgui.Render();
        imgui.End();
    }
    
    return 0;
}
