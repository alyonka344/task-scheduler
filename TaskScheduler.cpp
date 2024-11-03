#include "TaskScheduler.h"

TaskScheduler::TaskScheduler() : stop(false) {
    workerThread = std::thread(&TaskScheduler::Run, this);
}

TaskScheduler::~TaskScheduler() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
    workerThread.join();
}

void TaskScheduler::Add(std::function<void()> task, std::time_t timestamp) {
    std::lock_guard<std::mutex> lock(mtx);
    tasks.push({std::move(task), timestamp});
    cv.notify_one();
}


void TaskScheduler::Run() {
    while (true) {
        std::function<void()> task;


        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return stop || !tasks.empty(); });

        if (stop && tasks.empty()) {
            return;
        }

        auto now = std::time(nullptr);
        if (!tasks.empty() && tasks.top().timestamp <= now) {
            task = tasks.top().func;
            tasks.pop();
        }


        if (task) {
            task();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}