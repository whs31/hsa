//
// Created by whs31 on 11/1/2023.
//

#include "export/export.h"

#include <iostream>
#include <thread>

void readyRead()
{
  auto a = Read();
  std::cout << a.latitude << " " << a.longitude << " " << a.altitude << std::endl;
}

int main(int argc, char** argv)
{
  #if defined HSA_ENABLE_LOGGING
  std::cout << "HSA version " << PROJECT_VERSION << " started." << std::endl;
  #endif

  /*
   * thread_local asio::io_context io_context;
   * thread_local HSA::Adapter adapter(io_context);
   * io_context.run();
   */

  //EnableConsoleLogging();
  CreateAdapter();
  SetCallback(readyRead);
  Run();
  std::cin.get();
  Stop();
  FreeAdapter();
  std::cin.get();
  CreateAdapter();
  SetCallback(readyRead);
  Run();
  std::cin.get();
  Stop();
  FreeAdapter();
  std::this_thread::sleep_for((std::chrono::seconds(10)));

  return EXIT_SUCCESS;
}