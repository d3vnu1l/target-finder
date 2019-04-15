#pragma once

#include <chrono>
#include <thread>
#include <iostream>


class pixel_parser {
public:
    pixel_parser(const int worker_num) : _worker_num(worker_num) {}

    void init();

    void request_stop();

    void request_exit();

    void do_work(); 

private:

    int _worker_num;

    void parser_main();

    volatile bool _request_pause;
    volatile bool _request_exit;
    std::thread _thread;
};