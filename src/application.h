#pragma once

#include "imgui.h"
#include "model.h"
#include "controller.h"

/**
 * @brief The Application class represents the main application logic and UI rendering.
 */
class Application final
{
public:
    Application();
    ~Application();

    /**
     * @brief Update the application state.
     *
     * This method is called once per frame outside of the ImGui UI rendering context.
     * It can be used to update application logic or handle non-UI related tasks.
     */
    void update();

    /**
     * @brief Render the application UI.
     *
     * This method is called once per frame within the ImGui UI rendering context.
     * It is responsible for rendering the application's user interface using ImGui.
     */
    void render();



private:
    model::Model m_model;              ///< The application model containing the state and data.
    Controller m_controller;    ///< The controller responsible for handling user input and application logic.
    ImVec2 m_windowSize;        ///< The size of the application window.
};
