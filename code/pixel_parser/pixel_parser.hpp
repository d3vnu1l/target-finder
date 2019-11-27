#pragma once

#include <windows.h>
#include <future>
#include <mutex>
#include <thread>

#include "system_info.hpp"

class pixel_parser {
 public:
  pixel_parser(int worker_num, system_info* sys_info) : _worker_num(worker_num), _system(sys_info) {
    _thread = std::thread(&pixel_parser::parser_main, this);
  }

  enum class search_status { FAIL, SEARCHING, PASS };

  void init(std::promise<POINT>* prom_hit, HDC* screen, int granularity);

  void request_pause(volatile bool request_pause) { _request_pause = request_pause; }

  search_status search();

  bool is_paused() { return _request_pause; }

  std::thread* get_thread() { return &_thread; }

 private:
  int _worker_num;
  system_info* _system;
  int _granularity;
  volatile bool _request_pause = true;
  long _end_y;
  POINT _hit;
  POINT _seek;

  HDC* _screen;
  std::promise<POINT>* _prom_hit;
  std::thread _thread;
  void parser_main();
};