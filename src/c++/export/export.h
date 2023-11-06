//
// Created by whs31 on 03.11.2023.
//

#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-declarations"

//#include <thread>
#include "hsa.h"
#include "adapter.h"
#include "dgram.h"
#include "config/config.h"

static asio::io_context io_context;
static HSA::Adapter* adapter = nullptr;

extern "C" HSA_EXPORT void Run() { io_context.run(); }
extern "C" HSA_EXPORT void Stop() { io_context.stop(); }
extern "C" HSA_EXPORT void CreateAdapter() { adapter = new HSA::Adapter(io_context); }
extern "C" HSA_EXPORT void FreeAdapter() { delete adapter; adapter = nullptr; }
extern "C" HSA_EXPORT void SetCallback(HSA_TelemetryCallback callback) { adapter->setTelemetryUnmangledCallback(callback); }
extern "C" HSA_EXPORT HSA_Telemetry Read() { return adapter->telemetryUnmangled(); }
extern "C" HSA_EXPORT void SetConfigValue(const char* key, const char* value) { adapter->config()->setValueRaw(key, value); }

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