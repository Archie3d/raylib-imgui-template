#include "imgui.h"
#include "raylib.h"
#include "assets/fonts.h"
#include "application.h"

Application::Application(EventLoop& eventLoop)
    : m_eventLoop(eventLoop),
      m_model(),
      m_controller(m_model, m_eventLoop)
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
    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_MenuBar;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    // Main window
    ImGui::Begin("##mainWindow", nullptr, windowFlags);

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem(ICON_FK_SIGN_OUT " Exit")) {
                m_eventLoop.quit();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Text("This is a simple example of using ImGui with Raylib.");


    if (ImGui::Button("Click me", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
        //
    }

    ImGui::End();
}
