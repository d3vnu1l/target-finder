#include <iostream>

#include "target_finder.hpp"

void target_finder::status_screenshot_device() {
    int chunk_size = _system->get_y_res() / _threads;
    std::cout << "Detected resolution ";
    std::cout << _system->get_x_res() << "x" << _system->get_y_res() << "\n";  
    std::cout << "Threaded chunk Y size: " << chunk_size << std::endl;
}

bool target_finder::wait_for_match(std::promise<POINT>* prom, std::future<POINT>* fut) {
    while( true ) {
        bool scan = true;
        for(int i = 0; i < _threads; i++) {
            scan &=  _workers[i]->is_paused();
            if (std::future_status::ready == fut->wait_for(std::chrono::microseconds(10))) {
                return true;
            }
        }

        if ( scan &&  (std::future_status::ready != fut->wait_for(std::chrono::microseconds(0)))) { 
            return false;
        }
    }
}

POINT target_finder::find_target() {
    // Take screenshot
    _screen_shotter->screenshot();
    
    // Create thread result future
    std::promise<POINT> prom;
    std::future<POINT> fut = prom.get_future();

    // Start threads and wait for hit
    for (int index = 0; index < _threads; index++) { 
        _workers[index]->init(&prom, _screen_shotter->get_screen_bitmap(), _granularity); 
    }
    if ( wait_for_match(&prom, &fut) ) {
        for (auto& thread : _workers) { thread->request_pause(true); }
        _hit = fut.get();
    } else {
        _hit.x = -1;
    }
    
    return _hit;
}