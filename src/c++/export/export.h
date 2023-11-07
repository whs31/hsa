//
// Created by whs31 on 03.11.2023.
//

#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-declarations"

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
static unique_ptr<HSA::Adapter> adapter;
static unique_ptr<std::thread> t_ptr;

extern "C" HSA_EXPORT void Run()
{
  t_ptr = std::make_unique<std::thread>([](){
    #if defined(HSA_ENABLE_LOGGING)
    cout << "Thread detached" << endl;
    #endif

    asio::executor_work_guard<decltype(io_context.get_executor())> work_guard(io_context.get_executor());
    io_context.run();

    #if defined(HSA_ENABLE_LOGGING)
    cout << "Thread suspended" << endl;
    #endif

    t_ptr.reset(nullptr);
  });

  t_ptr->detach();
}

extern "C" HSA_EXPORT void Stop()
{
  io_context.stop();
}

extern "C" HSA_EXPORT void CreateAdapter() { adapter = std::make_unique<HSA::Adapter>(io_context); }
extern "C" HSA_EXPORT void FreeAdapter()
{
  adapter->socket()->stop();
  adapter.reset(nullptr);
}
extern "C" HSA_EXPORT void SetCallback(HSA_TelemetryCallback callback) { adapter->setTelemetryUnmangledCallback(callback); }
extern "C" HSA_EXPORT HSA_Telemetry Read() { return adapter->telemetryUnmangled(); }
extern "C" HSA_EXPORT void SetConfigValue(const char* key, const char* value) { adapter->config()->setValueRaw(key, value); }
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