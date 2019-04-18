#pragma once

#include <windows.h>
#include <iostream>

class screen_shotter {
public:
    screen_shotter(const POINT resolution) : _ptB(resolution) {
        _ptA.x = _ptA.y = 0;
    }

    bool screenshot();

    HDC* get_screen_bitmap() { return &_h_DC; }

    /// Save image to clipboard for testing purposes
    void save_to_clipboard();

private:
    POINT _ptB;
    POINT _ptA;
    HDC _h_DC;
    HBITMAP _h_bit_map;
};