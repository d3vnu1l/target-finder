#include "pixel_parser.hpp"

void pixel_parser::init() { _thread = std::thread(&pixel_parser::parser_main, this); } 

void request_stop() {

}

void request_exit() {
    
}

void pixel_parser::do_work() {

}

void pixel_parser::parser_main() {
    std::cout << _worker_num << std::endl;

    while(!_request_pause) {
        do_work();
    }
}