//
// Created by whs31 on 11/2/2023.
//

#pragma once

#include <string>
#include <Libra/Global>

using std::string;

namespace HSA
{
  struct UAVMetadata
  {
    u8 id;
    string name;
  };

  struct Telemetry
  {
    f64 latitude;
    f64 longitude;
    f64 latitude_d;
    f64 longitude_d;
    f32 altitude;
    f32 altitude_abs;
    u16 altitude_d;
    u64 timestamp;
    f32 acceleration_x;
    f32 acceleration_y;
    f32 acceleration_z;
    f32 col_pitch;
    f32 pitch;
    f32 roll;
    f32 yaw;
    f32 target_altitude;
    f32 target_speed;
    f32 throttle;
    f32 vx;
    f32 vy;
    f32 vz;
    i16 route_point;
    u8 route;
    u16 rpm_engine;
    u16 rpm_engine2;
    u16 rpm_rotor;
    u16 rpm_tail;
    u8 engine_state;
    u8 mode;
    u8 overriders_state;
    u8 override_altitude;
    u8 override_velocity;
    u8 override_yaw;
    u8 override_vz;
  };

  struct Datagram
  {
    UAVMetadata metadata;
    Telemetry telemetry;
  };
} // HSA
