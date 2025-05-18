#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "misc/cpp/imgui_stdlib.h" // stdlib support

class ImguiManager
{
private:
    GLFWwindow* m_window = nullptr;


private:
    void CreateDockspace();
public:
    ImguiManager(/* args */){};
    ~ImguiManager();

    bool initialize();
    void OnDetach();
    bool ShouldClose() const { return glfwWindowShouldClose(m_window); }
    void PollEvents() { glfwPollEvents(); }
    void Begin();
    void End();
    void Render();
};

