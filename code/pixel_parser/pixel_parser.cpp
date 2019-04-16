#include <iostream>
#include <chrono>

#include "pixel_parser.hpp"

void pixel_parser::init(std::promise<POINT>* prom_hit, HDC* screen, int start_y, int end_y) { 
    _screen = screen;
    _prom_hit = prom_hit;
    _seek.y = start_y;
    _end_y = end_y;
    _request_pause = false;
} 

// TODO: optimize
void pixel_parser::do_work() { 
    const int increment_x = 10;  // Check every x pixels

    if (_seek.y < _end_y) {
        for (_seek.x = 0; _seek.x < _resolution.x; _seek.x+=increment_x) {
            (void)GetPixel(*_screen, _seek.x, _seek.y);
        }
        _seek.y++;
    } else {
        _request_pause = true;
        _hit.x = _seek.y;
        _hit.y = _seek.x;
        _prom_hit->set_value(_hit);
    }
}

void pixel_parser::parser_main() {
    while (true) {
        while(!_request_pause) {
            do_work();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}