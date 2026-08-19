#pragma once

#include "event_loop.h"
#include "model.h"

/**
 * @brief The controller drives the application logic.
 *
 * The controller is responsible for mutatting the model
 * (which should happen on the main thread via the event loop).
 */
class Controller
{
public:
    Controller() = delete;
    Controller(model::Model& model, EventLoop& eventLoop);
    ~Controller();

    /**
     * @brief Schedule a function to be called on the main event loop.
     *
     * @param func The function to be executed.
     */
    void call(std::function<void()> func);

    /**
     * @brief Schedule a function to be called on the main event loop after a delay.
     *
     * @param func The function to be executed.
     * @param delayMs The delay in milliseconds before the function is executed.
     */
    void callDelayed(std::function<void()> func, long delayMs);

    /**
     * @brief Update the controller state.
     *
     * This method should be called periodically to process events and update the controller's state.
     */
    void update();

private:
    model::Model& m_model;
    EventLoop& m_eventLoop;
};