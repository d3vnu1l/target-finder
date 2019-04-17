#pragma once

#include <windows.h>
#include <thread>

class system_info {
public:

    system_info(const unsigned threads_to_use) : _threads_to_use(threads_to_use) {
        _num_threads_supported = std::thread::hardware_concurrency();
        if (2 > _num_threads_supported) { _num_threads_supported = 2; }
        
        SetProcessDPIAware();
        _resolution.x = GetSystemMetrics(SM_CXSCREEN);
        _resolution.y = GetSystemMetrics(SM_CYSCREEN); 
    }

    long get_x_res() { return _resolution.x; }
    long get_y_res() { return _resolution.y; }
    POINT get_res() { return _resolution; }

    unsigned get_threads_count() { return _threads_to_use; }
    unsigned get_threads_supported() { return _num_threads_supported; }

private:

    unsigned _num_threads_supported;
    unsigned _threads_to_use;
    POINT _resolution;
};