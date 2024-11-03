#include <iostream>
#include "TaskScheduler.h"

int main() {
    TaskScheduler scheduler;

    std::time_t now = std::time(nullptr);
    scheduler.Add([] { std::cout << "Task 1 executed at " << std::time(nullptr) << "\n"; }, now + 20);
    scheduler.Add([] { std::cout << "Task 2 executed at " << std::time(nullptr) << "\n"; }, now + 5);
    scheduler.Add([] { std::cout << "Task 3 executed at " << std::time(nullptr) << "\n"; }, now + 10);

    return 0;
}
