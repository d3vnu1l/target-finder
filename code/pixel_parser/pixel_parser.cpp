#include <iostream>
#include <chrono>

#include "pixel_parser.hpp"

void pixel_parser::init(std::promise<POINT>* prom_hit, HDC* screen, int granularity) { 
    const long chunk_size = (_system->get_y_res() / _system->get_threads_count());
    _seek.y = (_worker_num  * chunk_size);
    _end_y = _seek.y + chunk_size;

    _granularity = granularity;
    _screen = screen;
    _prom_hit = prom_hit;
    _request_pause = false;
} 

// TODO: optimize
void pixel_parser::do_work() { 
    const long x_res = _system->get_x_res();
   
    if (_seek.y < _end_y) {
        _seek.x = 0;    // TODO: stagger

        for (; _seek.x < x_res; _seek.x+= _granularity) {
            if(2359525 == GetPixel(*_screen, _seek.x, _seek.y)) {
                // TODO prevent multiple threads using promise at once
                _hit.x = _seek.x;
                _hit.y = _seek.y;
                //if (_worker_num == 0) { 
                    _request_pause = true;
                    _prom_hit->set_value(_hit); 
                    break; 
                //} // TODO move this to hit
            }
            else {
                _hit.x = 0;
                _hit.y = 0;
            }
        }
        _seek.y+= _granularity;
    } else {
        // Target not found, pause
        _request_pause = true;

        if (_worker_num == 0) { _prom_hit->set_value(_hit); } // TODO move this to hit
    }
}

void pixel_parser::parser_main() {
    while (true) {
        while(!_request_pause) {
            do_work();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
}