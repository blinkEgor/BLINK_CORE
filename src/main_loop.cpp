#include "../include/main_loop.h"

int main_loop::max_i = 100;    // -1 is infinity
int main_loop::cur_i = 0;
bool main_loop::start = false;

bool main_loop::loop() {
    blink_logger::log( "Main loop was started", log_level::INFO );
    blink_logger::log( "Start status: " + start ? "true" : "false" , log_level::DEBUG );
    do {
        cur_i++;
        if ( max_i > 0 && cur_i >= max_i ) {
            blink_logger::log( "Reached max iterations: " + std::to_string( max_i ), log_level::DEBUG );
            break;
        }
    } while ( start );
    
    return true;
}
