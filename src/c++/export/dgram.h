//
// Created by whs31 on 11/5/2023.
//

#pragma once

#include "hsa.h"
#include <Libra/Global>

extern "C"
{
  typedef void (*HSA_TelemetryCallback)();
  struct HSA_EXPORT HSA_Telemetry
  {
    f64 latitude;
    f64 longitude;
    f32 altitude;
  };
}
