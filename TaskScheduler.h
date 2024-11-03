#include <iostream>
#include <functional>
#include <ctime>
#include <thread>
#include <condition_variable>
#include <queue>
#include <utility>

class TaskScheduler {
public:
    TaskScheduler();
    ~TaskScheduler();
    void Add(std::function<void()> task, std::time_t timestamp);

private:
    struct Task {
        std::function<void()> func;
        std::time_t timestamp;
    };

    static bool Compare(const Task& a, const Task& b)  {
        return a.timestamp > b.timestamp;
    };

    std::thread workerThread;
    bool stop;
    std::mutex mtx;
    std::condition_variable cv;
    std::priority_queue<Task, std::vector<Task>, decltype(&Compare)> tasks{Compare};

    void Run();
};
