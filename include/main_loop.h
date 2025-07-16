#pragma once
#include "../include/blink_core/logger.h"

namespace main_loop {
    extern int max_i;
    extern int cur_i;
    extern bool start;
    bool loop();
}