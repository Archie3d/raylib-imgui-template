#pragma once

#include <memory>
#include <chrono>
#include <functional>

/**
 * Event loop.
 *
 * The event loops manages a queue of events with timestamped functors.
 * The execution loop iterates through the events in the queue and invokes
 * those scheduled to be executed considering the timestamp and current
 * monitomic system time.
 */
class EventLoop final
{
public:

    using Handler = std::function<void()>;
    using Timestamp = std::chrono::steady_clock::time_point;

    /**
     * Construct the event loop but do not run it.
     */
    EventLoop();

    EventLoop(EventLoop&& other);
    EventLoop(const EventLoop&) = delete;
    EventLoop& operator =(const EventLoop&) = delete;

    /**
     * Destroy the event loop and all the queued events.
     *
     * @note All pending messages will not be processed.
     */
    ~EventLoop();

    /**
     * Run the event loop.
     *
     * This method blocks waiting on the events coming to the events queue.
     * The loop can be interrupted by calling quit() method.
     * On termination the method returns the exit code passed by the quit() method.
     *
     * When there are not events in the queue the method will sleep waiting for
     * the incoming events.
     *
     * @return Exit code.
     */
    int exec();

    /**
     * Terminate the event loop.
     *
     * @param code Return code that will be passed and returned by exec() method.
     */
    void quit(int code = 0);

    /**
     * Process all the pending events in the queue.
     */
    void processEvents();

    /**
     * Process all pending events in the queue and terminate the loop.
     *
     * @param code Exit code.
     */
    void processEventsAndQuit(int code = 0);

    /**
     * Emit an event to be processed immediately.
     *
     * @param handler Event functor.
     */
    void emit(Handler handler);

    /**
     * Emit an event to be processed after specific time period.
     *
     * This method adds the event to the queue. The event will be processed
     * ony when the given time period gets elapsed.
     *
     * @param handler Event functor.
     * @param delayMs Time period in ms.
     */
    void emitDelayed(Handler handler, long delayMs);

    /**
     * Emit an event to pe processed on specific time.
     *
     * This method adds the event to the queue. The event will be processed
     * only when the system steady clock reaches the timespamp specified.
     * If the event timestamp lags behind the system clock the event gets
     * processed immediately.
     *
     * @param handler Event functor.
     * @param ts Event absolute timestamp.
     */
    void emitOnTime(Handler handler, const Timestamp& ts);

    bool isRunning() const;

    int getExitCode() const;

private:

    struct Impl;
    std::unique_ptr<Impl> d;
};
