#include <iostream>
#include <chrono>

#include "pixel_parser.hpp"

void pixel_parser::init() { _thread = std::thread(&pixel_parser::parser_main, this); } 

void request_stop() {

}

void kill() {
    std::terminate();
}

void pixel_parser::do_work() {
    std::cout << _worker_num << std::flush;
}

void pixel_parser::parser_main() {
    while(!_request_pause) {
        std::this_thread::sleep_for(std::chrono::milliseconds(_worker_num*100));
        do_work();
    }
}