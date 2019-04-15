#pragma once

#include <iostream>
#include <windows.h>

class screen_shotter {
public:
    screen_shotter(const int xRes, const int yRes) {
        _ptA.x = 0;
        _ptA.y = 0;
        _ptB.x = xRes;
        _ptB.y = yRes;
    }

    void screenshot();

    void save_to_clipboard();

private:

    HDC _hScreen;
    HDC _hDC;
    HBITMAP _hBitMap;
    HGDIOBJ _oldObj;
    POINT _ptA;
    POINT _ptB;
};