#include <chrono>
#include "TimeManager.hh"

TimeManager::TimeManager() {
    
}

TimeManager::~TimeManager() {
    
}

TimeManager& TimeManager::GetInstance() {
    static TimeManager _instance;
    return _instance;
}

void TimeManager::Start() {
    start_time = std::chrono::steady_clock::now();
    update_first_time = std::chrono::steady_clock::now();
    update_last_time = std::chrono::steady_clock::now();
}

void TimeManager::Update() {
    update_first_time = update_last_time;
    update_last_time = std::chrono::steady_clock::now();
}

unsigned int TimeManager::GetElapsedTime() const {
    auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(update_last_time - update_first_time).count();
    return (unsigned int) elapsed_milliseconds;
}

unsigned int TimeManager::GetStartedTime() const {
    return (unsigned int) std::chrono::duration_cast<std::chrono::milliseconds>(update_last_time - start_time).count();
}