#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <array>
#include <io.h>
#include <fstream>
#include <fcntl.h>
#include <future>
#include <csignal>

#include "pixel_parser.hpp"
#include "screen_shotter.hpp"
#include "system_info.hpp"

using namespace std;

static void redirect_io_to_console() {
    if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
}

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    const unsigned threads = 30;  // TODO : cmd line
    const int fps = 4;            // TODO : cmd line
    const int granularity = 10;   // TODO : cmd line
    const int time_slot_us = ((1000 * 1000)/fps);

    redirect_io_to_console();

    // Get resolution and configure screenshotter
    system_info* _system = new system_info(threads);
    cout << "Detected resolution ";
    cout << _system->get_x_res() << "x" << _system->get_y_res() << "\n";  
    screen_shotter _screen_shotter(_system->get_res());
    int chunk_size = _system->get_y_res() / threads;
    cout << "Threaded chunk Y size: " << chunk_size << endl;

    // Create thread result promise
    promise<POINT> prom;
    future<POINT> fut = prom.get_future();
    
    // Create threads
    array<unique_ptr<pixel_parser>, threads > workers;
    for (int index = 0; index < threads; index++) {
        workers[index] = unique_ptr<pixel_parser>(new pixel_parser(index, _system));
    }

    // Run until ctrl-c
    static bool continue_running = true;
    auto sigint_lambda = [](int signal) { continue_running = false; };
    signal(SIGINT, sigint_lambda);
    while (continue_running) {
        auto start = std::chrono::high_resolution_clock::now();

        // Get screenshot
        if (_screen_shotter.screenshot()) {
            // Start threads and wait for hit
            for (auto& thread : workers) { 
                thread->init(&prom, _screen_shotter.get_screen_bitmap(), granularity); 
            }
            POINT hit = fut.get();

            // Pause all of the threads
            for (auto& thread : workers) { thread->request_pause(true); }
            std::this_thread::sleep_for(std::chrono::microseconds(200));  // TODO: Need to be sure all threads exit

            // Reset promise
            prom = std::promise<POINT>();
            fut = prom.get_future();

            cout << hit.x << "x" << hit.y << " ";
        }

        // Maintain timing
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        int us_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        cout <<  (100.0*us_elapsed/time_slot_us) << "% load\n";
        if (us_elapsed > time_slot_us) {
            cout << "Overload!\n";
        } else {
            std::this_thread::sleep_for(std::chrono::microseconds(time_slot_us - us_elapsed));
        }
    }

    cout << "Quiting...\n";
    return 0;
}
