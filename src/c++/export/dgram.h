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
    // heli_telemetry
    f64 latitude;
    f64 longitude;
    f32 altitude;
    f32 altitude_abs;
    f32 col_pitch;
    f32 pitch;
    f32 roll;
    f32 yaw;
    f32 throttle;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 rpm_engine;
    f32 rpm_rotor;
    f32 rpm_tail;
    u8 engine_state;
    u8 autopilot_mode;
    // status

    // navio
    f32 altitude_barometric;
    f32 altitude_gps;
    f32 altitude_radio;
  };
}
