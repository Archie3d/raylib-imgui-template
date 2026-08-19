#include <iostream>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "extras/FA6FreeSolidFontData.h"
#include "extras/IconsFontAwesome6.h"
#include "assets/fonts.h"

constexpr float kDefaultFontSize = 10.0f;
constexpr int kDefaultWindowWidth = 1280;
constexpr int kDefaultWindowHeight = 800;

void loadFonts(float scale)
{
    if (scale <= 0.0f) {
        scale = 1.0f;
    }

    auto& io = ImGui::GetIO();

    // Main body font
    ImFontConfig uiFontConfig;
    uiFontConfig.FontDataOwnedByAtlas = false;

    const float uiFontSize = kDefaultFontSize * scale;

    ImFont* uiFont = io.Fonts->AddFontFromMemoryTTF(
        (void*)assets::DMSANS_REGULAR_TTF.data(),
        assets::DMSANS_REGULAR_TTF.size(),
        uiFontSize,
        &uiFontConfig
    );
    io.FontDefault = uiFont;

    // Icons font
    ImFontConfig iconsFontConfig;
    iconsFontConfig.MergeMode = true;
    iconsFontConfig.PixelSnapH = true;
    iconsFontConfig.FontDataOwnedByAtlas = false;

    static const ImWchar icon_ranges[] = { ICON_MIN_FK, ICON_MAX_FK, 0 };

    ImFont* iconsFont = io.Fonts->AddFontFromMemoryTTF(
        (void*)assets::FORKAWESOME_WEBFONT_TTF.data(),
        assets::FORKAWESOME_WEBFONT_TTF.size(),
        0.0f,
        &iconsFontConfig,
        icon_ranges
    );
}

void applyDpiScale(float scale)
{
    auto& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();

    style.ScaleAllSizes(scale);
    style.WindowRounding = 6.0f * scale;
    style.FrameRounding = 6.0f * scale;
    style.FrameBorderSize = 1.0f * scale;
    style.FontScaleDpi = 1.0f; // Fonts are already scaled during loading.

    auto& io = ImGui::GetIO();

    if (!io.Fonts->Fonts.empty()) {
        io.FontDefault = nullptr;
        io.Fonts->Clear();
    }

    loadFonts(scale);
}

int main(int argc, char* argv[])
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
    InitWindow(kDefaultWindowWidth, kDefaultWindowHeight, "Raylib + ImGui Template");
    SetTargetFPS(60);

    rlImGuiSetup(true); // This will create and own ImGui context.

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr; // Disable imgui.ini file
    io.LogFilename = nullptr; // Disable imgui_log.txt file
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    const auto dpiScale = GetWindowScaleDPI();
    applyDpiScale(dpiScale.y);

    std::cout << "DPI Scale: " << dpiScale.x << ", " << dpiScale.y << std::endl;

    if (!IsWindowState(FLAG_WINDOW_HIGHDPI)) {
        io.DisplayFramebufferScale = ImVec2(dpiScale.x, dpiScale.y);
    }

    ImGui::StyleColorsDark();

    rlImGuiSetup(true);

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Start the ImGui frame
        rlImGuiBegin();

        // Create a simple ImGui window
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a simple example of using ImGui with Raylib.");
        if (ImGui::Button(ICON_FK_BOOK " Click Me"))
        {
            // Handle button click
        }
        ImGui::End();

        // End the ImGui frame
        rlImGuiEnd();

        EndDrawing();
    }

    // Cleanup
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
