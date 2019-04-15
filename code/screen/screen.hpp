#pragma once

#include <windows.h>

class screen {
public:

    screen() {
        SetProcessDPIAware();
        _resolution.x = GetSystemMetrics(SM_CXSCREEN);
        _resolution.y = GetSystemMetrics(SM_CYSCREEN);
    }

    long get_x_res() { return _resolution.x; }

    long get_y_res() { return _resolution.y; }

    POINT get_res() { return _resolution; }

private:

    POINT _resolution;
};