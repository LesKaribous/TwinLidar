#pragma once

namespace Led{
    void init();
    void update();

    void setFullColor(long unsigned int);

    void idle();
    void ready();
    void detect();
} // namespace LED
