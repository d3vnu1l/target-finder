#include <iostream>

#include "target_finder.hpp"

void target_finder::status_screenshot_device() {
    int chunk_size = _system->get_y_res() / _threads;
    std::cout << "Detected resolution ";
    std::cout << _system->get_x_res() << "x" << _system->get_y_res() << "\n";  
    std::cout << "Threaded chunk Y size: " << chunk_size << std::endl;
}

POINT target_finder::find_target() {
    // Take screenshot
    _screen_shotter->screenshot();
    
    // Create thread result future
    std::promise<POINT> _prom;
    std::future<POINT> _fut = _prom.get_future();

    // Start threads and wait for hit
    for (int index = 0; index < _threads; index++) { 
        _workers[index]->init(&_prom, _screen_shotter->get_screen_bitmap(), _granularity); 
    }
    _hit = _fut.get();

    std::this_thread::sleep_for(std::chrono::microseconds(1200));  // TODO: Need to be sure all threads exit

    // Pause all of the threads & return
    for (auto& thread : _workers) { thread->request_pause(true); }
    return _hit;
}