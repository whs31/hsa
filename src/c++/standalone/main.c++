//
// Created by whs31 on 11/1/2023.
//

#include "adapter.h"

#if defined HSA_ENABLE_LOGGING
#include <iostream>
#endif


int main(int argc, char** argv)
{
  #if defined HSA_ENABLE_LOGGING
  std::cout << "HSA version " << PROJECT_VERSION << " started." << std::endl;
  #endif

  thread_local asio::io_context io_context;
  HSA::Adapter adapter(io_context);
  io_context.run();

  return EXIT_SUCCESS;
}