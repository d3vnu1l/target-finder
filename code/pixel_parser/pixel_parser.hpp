#pragma once

#include <thread>

class pixel_parser {
public:
    pixel_parser(const int worker_num) : _worker_num(worker_num) { 
        _request_pause = false;
    }

    void init();

    void request_stop();

    void kill();

    void do_work(); 

    std::thread* get_thread() { return &_thread; }

    //void set_worker_num(const int worker_num) { _worker_num = worker_num; }

private:
    int _worker_num;

    void parser_main();

    volatile bool _request_pause;
    std::thread _thread;
};