
#ifndef TimeManager_hh
#define TimeManager_hh

#include <stdio.h>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include <iostream>

class TimeManager {
    
private:
    TimeManager();
    ~TimeManager();
    TimeManager(const TimeManager&) = delete;
    TimeManager& operator=(const TimeManager&) = delete;
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point update_last_time;
    std::chrono::steady_clock::time_point update_first_time;

    
public:
    static TimeManager& GetInstance();

    void Start();
    void Update();
    unsigned int GetElapsedTime() const;
    unsigned int GetStartedTime() const;

};
#endif /* TimeManager_hh */