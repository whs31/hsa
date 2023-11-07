//
// Created by whs31 on 03.11.2023.
//

#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-declarations"

#include <memory>
#include <thread>
#include "hsa.h"
#include "adapter.h"
#include "dgram.h"
#include "config/config.h"
#include "ip/socketasio.h"

#if defined(HSA_ENABLE_LOGGING)
#include "utility/clilogger.h"
#include <iostream>

using std::cout;
using std::endl;
#endif

static asio::io_context io_context;
static HSA::Adapter adapter(io_context);

extern "C" HSA_EXPORT void Stop()
{
  io_context.stop();
  adapter.stop();
}

extern "C" HSA_EXPORT void Run(HSA_TelemetryCallback callback)
{
  adapter.setTelemetryUnmangledCallback(callback);
  adapter.start();
  std::thread t ([](){

    #if defined(HSA_ENABLE_LOGGING)
    cout << "Thread detached" << endl;
    #endif

    io_context.run();
    io_context.restart();

    #if defined(HSA_ENABLE_LOGGING)
    cout << "Thread suspended" << endl;
    #endif
  });

  t.detach();
}

extern "C" HSA_EXPORT HSA_Telemetry Read() { return adapter.telemetryUnmangled(); }
extern "C" HSA_EXPORT void SetConfigValue(const char* key, const char* value) { adapter.config()->setValueRaw(key, value); }
extern "C" HSA_EXPORT void EnableConsoleLogging() {
  #if defined(HSA_ENABLE_LOGGING)
  HSA::Console::EnableConsole();
  #endif
}

extern "C" HSA_EXPORT const char* Version() { return PROJECT_VERSION; }
extern "C" HSA_EXPORT bool IsWin32()
{
  #if defined(LIBRA_OS_WINDOWS)
  return true;
  #else
  return false;
  #endif
}
extern "C" HSA_EXPORT bool IsPOSIX()
{
  #if defined(LIBRA_OS_LINUX)
  return true;
  #else
  return false;
  #endif
}

#pragma clang diagnostic pop