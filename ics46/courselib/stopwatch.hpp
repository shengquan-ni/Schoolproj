#ifndef STOPWATCH_HPP_
#define STOPWATCH_HPP_

#include <ctime>

namespace ics {

class Stopwatch {
public:
    Stopwatch(bool running_now = false, bool running_forward = true, long elapsed_prior = 0, std::clock_t last_start_time = 0);

    void reset();

    void start();

    void start_backwards();

    void stop();

    double read();

private:
    bool running_now;
    bool running_forward;
    long elapsed_prior;
    std::clock_t last_start_time;
    void update() {
        elapsed_prior  += (running_forward ? 1 : -1) * (std::clock() - last_start_time);
        last_start_time  = std::clock();
    }

    friend std::ostream& operator << (std::ostream& outs, const Stopwatch& s);

};


}

#endif /* STOPWATCH_HPP_ */
