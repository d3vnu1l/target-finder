#pragma once

#include <windows.h>
#include <thread>
#include <future>
#include <mutex>

class pixel_parser {
public:
    pixel_parser(const int worker_num, const POINT resolution) : _worker_num(worker_num), _resolution(resolution) { 
        _request_pause = true;
        _thread = std::thread(&pixel_parser::parser_main, this); 
    }

    void init(std::promise<POINT>* prom_hit, HDC *screen, int start_y, int end_y);

    void request_pause(volatile bool request_pause) { _request_pause = request_pause; }

    void do_work(); 

    std::thread* get_thread() { return &_thread; }

    //void set_worker_num(const int worker_num) { _worker_num = worker_num; }

private:
    int _worker_num;
    POINT _resolution;

    void parser_main();

    HDC* _screen;
    POINT _hit;
    POINT _seek;
    long  _end_y;
    std::promise<POINT>* _prom_hit;
    volatile bool _request_pause;
    std::thread _thread;
};