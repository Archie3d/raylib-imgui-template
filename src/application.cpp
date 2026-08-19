#include "imgui.h"
#include "raylib.h"
#include "assets/fonts.h"
#include "application.h"

Application::Application()
    : m_model(),
      m_controller(m_model)
{
    m_windowSize = ImVec2(static_cast<float>(GetScreenWidth()),
                          static_cast<float>(GetScreenHeight()));
}

Application::~Application() = default;

void Application::update()
{
    // Capture current window size
    if (IsWindowResized()) {
        m_windowSize = ImVec2(static_cast<float>(GetScreenWidth()),
                              static_cast<float>(GetScreenHeight()));
    }

    m_controller.update();
}

void Application::render()
{
    // Create a simple ImGui window
    ImGui::Begin("Hello, ImGui!");
    ImGui::Text("This is a simple example of using ImGui with Raylib.");
    if (ImGui::Button(ICON_FK_BOOK " Click Me"))
    {
        // Handle button click
    }
    ImGui::End();
}
