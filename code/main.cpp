#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <io.h>
#include <fstream>
#include <fcntl.h>
#include <csignal>

#include "target_finder.hpp"

using namespace std;

static void redirect_io_to_console() {
    if(AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()){
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
}

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    const unsigned threads = 12;   // TODO : cmd line
    const int fps = 5;            // TODO : cmd line
    const int granularity = 10;   // TODO : cmd line
    const long time_slot_us = ((1000 * 1000)/fps);

    redirect_io_to_console();

    // Instantiate target_finder
    target_finder* _target_finder = new target_finder(threads, granularity);
    _target_finder->status_screenshot_device();

    // Run until ctrl-c
    static bool continue_running = true;
    auto sigint_lambda = [](int signal) { continue_running = false; };
    signal(SIGINT, sigint_lambda);
    while (continue_running) {
        auto start = std::chrono::high_resolution_clock::now();

        POINT hit;
        hit = _target_finder->find_target();
        if (hit.x != -1) { cout << "Spotted: " << hit.x << "x" << hit.y << "    ";}

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
