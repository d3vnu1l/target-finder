#pragma once

#include <windows.h>
#include <iostream>

class screen_shotter {
public:
    screen_shotter(const POINT resolution) {
        _ptA.x = 0;
        _ptA.y = 0;
        _ptB.x = resolution.x;
        _ptB.y = resolution.y;
    }

    bool screenshot();

    HDC* get_screen_bitmap() { return &_h_DC; }

    /// Save image to clipboard for testing purposes
    void save_to_clipboard();

private:

    HDC _h_DC;
    HBITMAP _h_bit_map;
    POINT _ptA;
    POINT _ptB;
};