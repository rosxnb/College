#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <iomanip>
#include <chrono>

class Timer
{
    using steady_clock = std::chrono::steady_clock;
    using nanoseconds = std::chrono::nanoseconds;
    template<typename clock>
    using time_point = std::chrono::time_point<clock>;
    template<typename representation, typename precision>
    using duration = std::chrono::duration<representation, precision>;

private:
    time_point<steady_clock> tp_start, tp_end;
    void stop_timer();

public:
    Timer();
    ~Timer();
};

Timer::Timer()
    : tp_start {steady_clock::now()}
{ }

void Timer::stop_timer()
{
    tp_end = steady_clock::now();

    nanoseconds t_nano {tp_end - tp_start};
    duration<double, std::micro> t_micro {t_nano};
    duration<double, std::milli> t_milli {t_nano};
    duration<double, std::ratio<1>> t_sec {t_nano};

    std::cout << "\n time taken: \n" << std::fixed << std::setprecision(2);
    std::cout << "\t |- " << t_nano.count() << " ns \n";
    std::cout << "\t |- " << t_micro.count() << " µs \n";
    std::cout << "\t |- " << t_milli.count() << " ms \n";
    std::cout << "\t |- " << t_sec.count() << " s \n";
}

Timer::~Timer()
{ 
    stop_timer();
}

#endif
