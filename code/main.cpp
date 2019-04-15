#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <array>
#include <io.h>
#include <fstream>
#include <fcntl.h>

#include "pixel_parser.hpp"
#include "screen_shotter.hpp"

using namespace std;

void main();

static void redirect_io(){
    if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
}

static POINT get_resolution() {
    POINT resolution;

    SetProcessDPIAware();
    resolution.x = GetSystemMetrics(SM_CXSCREEN);
    resolution.y = GetSystemMetrics(SM_CYSCREEN);

    return resolution;
}

void target_finder() {
    const int threads = 1;

    cout << "\nProgram Starting...\n";

    // Get resolution
    POINT resolution = get_resolution();
    cout << "Detected resolution " << resolution.x << "x" << resolution.y << endl;

    screen_shotter _screen_shotter(resolution.x, resolution.y);
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
    /**
     * ...
     */

    cout << endl;
    system("pause");
}

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    redirect_io();
    target_finder();

    return 0;
}