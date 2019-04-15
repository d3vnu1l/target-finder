#include <stdio.h>
#include <iostream>
#include <thread>
#include <array>

#include "pixel_parser.hpp"
#include "screen_shotter.hpp"
#include <windows.h>
using namespace std;

void main();

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, INT nCmdShow)
{
    main();

    return 0;
}

void main() {

    const int threads = 1;
    const int xRes = 1920;
    const int yRes = 1080;

    cout << "Program Starting...\n";

    screen_shotter _screen_shotter(xRes, yRes);

    _screen_shotter.screenshot();
    _screen_shotter.save_to_clipboard();
   
    /*
    std::array<std::unique_ptr<worker>, threads> workers = {
        std::unique_ptr<worker>(new pixel_parser()),
    };

   for (auto& thread : workers) {
    worker->init();
    }
    */

  // start here.
}