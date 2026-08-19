#include "controller.h"


Controller::Controller(model::Model& model, EventLoop& eventLoop)
    : m_model(model),
      m_eventLoop(eventLoop)
{
}

Controller::~Controller() = default;

void Controller::call(std::function<void()> func)
{
    m_eventLoop.emit(std::move(func));
}

void Controller::callDelayed(std::function<void()> func, long delayMs)
{
    m_eventLoop.emitDelayed(std::move(func), delayMs);
}

void Controller::update()
{
    m_eventLoop.processEvents();
}
