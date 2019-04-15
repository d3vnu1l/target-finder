#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <array>
#include <io.h>
#include <fstream>
#include <fcntl.h>

#include "pixel_parser.hpp"
#include "screen_shotter.hpp"
#include "screen.hpp"

static void redirect_io_to_console(){
    if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
}

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    const size_t threads = 8;
    redirect_io_to_console();

    std::cout << "\nProgram Starting...\n";

    // Get resolution
    screen* _screen = new screen();
    std::cout << "Detected resolution ";
    std::cout << _screen->get_x_res() << "x" << _screen->get_y_res() << "\n";

    screen_shotter _screen_shotter(_screen->get_res());
    if (_screen_shotter.screenshot()) {
        std::cout << "Screenshot successful!\n";
    }
    // _screen_shotter.save_to_clipboard();    
   
    // Create threads
    std::array<std::unique_ptr<pixel_parser>, threads> workers;
    for (int index = 0; index < threads; index++) {
        workers[index] = std::unique_ptr<pixel_parser>(new pixel_parser(index + 1));
    }

   for (auto& thread : workers) {
        thread->init();
    }

    // Get screenshot
    // update threads
    // wait for hit and pause threads
    // repeat

    workers[0]->get_thread()->join();

    std::cout << std::endl;
    system("pause");
    return 0;
}
