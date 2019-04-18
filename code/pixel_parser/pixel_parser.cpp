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
pixel_parser::search_status pixel_parser::search() { 
    const long x_res = _system->get_x_res();
   
    if (_seek.y < _end_y) {
        _seek.x = 0;    // TODO: stagger

        for (; _seek.x < x_res; _seek.x+= _granularity) {
            if(2359525 == GetPixel(*_screen, _seek.x, _seek.y)) {
                _hit.x = _seek.x;
                _hit.y = _seek.y;
                return search_status::PASS;
            }
            else {
                _hit.x = -1;
            }
        }
        _seek.y+= _granularity;
    } else {
        return search_status::FAIL;
    }

    return search_status::SEARCHING;
}

void pixel_parser::parser_main() {
    while (true) {
        while(!_request_pause) {
            switch(search()){
                case search_status::PASS:
                    _prom_hit->set_value(_hit);
                case search_status::FAIL:
                    _request_pause = true;
                case search_status::SEARCHING:
                    break;
            }
        }

        std::this_thread::sleep_for(std::chrono::microseconds(1000));
    }
}