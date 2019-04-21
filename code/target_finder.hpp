#pragma once

#include <windows.h>
#include <future>
#include <memory>
#include <vector>

#include "screen_shotter.hpp"
#include "pixel_parser.hpp"
#include "system_info.hpp"

class target_finder {
public:
    target_finder(const unsigned threads, const int granularity)
                    : _threads(threads), _granularity(granularity) {
        _hit.x = _hit.y = 0;
        _system = new system_info(_threads);
        _screen_shotter = new screen_shotter(_system->get_res());
        for (int index = 0; index < _threads; index++) {
            _workers.push_back(std::unique_ptr<pixel_parser>(new pixel_parser(index, _system)));
        }
    }

POINT find_target();

void status_screenshot_device();

private:
    const unsigned _threads; 
    const int _granularity;
    POINT _hit;

    std::vector<std::unique_ptr<pixel_parser>> _workers;
    screen_shotter* _screen_shotter;
    system_info* _system;
    bool wait_for_match(std::promise<POINT>* prom, std::future<POINT>* fut);
};