#include "screen_shotter.hpp"

bool screen_shotter::screenshot() {
    _hScreen = GetDC(NULL);
    _hDC = CreateCompatibleDC(_hScreen);
    _hBitMap = CreateCompatibleBitmap(_hScreen, abs(_ptB.x-_ptA.x), abs(_ptB.y-_ptA.y));
    _oldObj = SelectObject(_hDC, _hBitMap);
    return(BitBlt(_hDC, 0, 0, abs(_ptB.x-_ptA.x), abs(_ptB.y-_ptA.y), _hScreen, _ptA.x, _ptA.y, SRCCOPY));
}

void screen_shotter::save_to_clipboard() {
    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, _hBitMap);
    CloseClipboard();
}