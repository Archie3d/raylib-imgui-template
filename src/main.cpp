#include <cassert>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "assets/fonts.h"
#include "event_loop.h"
#include "application.h"

constexpr float kDefaultFontSize = 10.0f;
constexpr int kDefaultWindowWidth = 1280;
constexpr int kDefaultWindowHeight = 800;

extern "C" {
    struct GLFWwindow;
    using GLFWwindowrefreshfun = void (*)(GLFWwindow*);
    GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow* window, GLFWwindowrefreshfun callback);
    void glfwSetWindowUserPointer(GLFWwindow* window, void* pointer);
    void* glfwGetWindowUserPointer(GLFWwindow* window);
    GLFWwindow* glfwGetCurrentContext(void);
}

/**
 * @brief Load the main UI font and the icons font.
 *
 * The fonts are loaded from static memory (see assets/fonts.h)
 * and are scaled according to the provided scale factor.
 */
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

/**
 * @brief Rescale the UI to match the provided DPI scale factor.
 *
 * @note This will also reload the fonts.
 */
void applyDpiScale(float scale)
{
    auto& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();

    style.ScaleAllSizes(scale);
    style.WindowRounding = 0.0f * scale;
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

void renderFrame(Application& app)
{
    app.update();

    BeginDrawing();
    ClearBackground(DARKGRAY);

    rlImGuiBegin();
    app.render();
    rlImGuiEnd();

    EndDrawing();
}

static void windowRefreshCallback(GLFWwindow* window)
{
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    assert(app != nullptr && "Application pointer has not been set by glfwSetWindowUserPointer()");
    renderFrame(*app);
}

int main(int argc, char* argv[])
{
#if defined(_DEBUG) || defined(DEBUG)
    SetTraceLogLevel(LOG_DEBUG);
#else
    SetTraceLogLevel(LOG_WARNING);
#endif

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

    if (!IsWindowState(FLAG_WINDOW_HIGHDPI)) {
        io.DisplayFramebufferScale = ImVec2(dpiScale.x, dpiScale.y);
    }

    ImGui::StyleColorsDark();

    rlImGuiSetup(true);

    EventLoop eventLoop;
    Application app(eventLoop);

    // Install GLFW window refresh callback to repaint the window when resizing.
    auto* glfwWindow = glfwGetCurrentContext();
    glfwSetWindowUserPointer(glfwWindow, &app);
    glfwSetWindowRefreshCallback(glfwWindow, windowRefreshCallback);

    while (!WindowShouldClose() && eventLoop.isRunning())
    {
        renderFrame(app);
    }

    // Cleanup
    rlImGuiShutdown();
    CloseWindow();

    return eventLoop.getExitCode();
}
