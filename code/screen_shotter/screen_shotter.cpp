#include "screen_shotter.hpp"

bool screen_shotter::screenshot() {
    bool success = false;

    DeleteDC(_h_DC);     // Delete objects assuming we've already run once
    DeleteObject(_h_bit_map);

    HDC h_screen = GetDC(NULL);
    _h_DC = CreateCompatibleDC(h_screen);
    _h_bit_map = CreateCompatibleBitmap(h_screen, abs(_ptB.x-_ptA.x), abs(_ptB.y-_ptA.y));
    HGDIOBJ _oldObj = SelectObject(_h_DC, _h_bit_map);
    success = BitBlt(_h_DC, 0, 0, abs(_ptB.x-_ptA.x), abs(_ptB.y-_ptA.y), h_screen, _ptA.x, _ptA.y, SRCCOPY);
    
    DeleteObject(_oldObj);
    DeleteDC(h_screen);

    return success;
}

void screen_shotter::save_to_clipboard() {
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, _h_bit_map);
    CloseClipboard();
}