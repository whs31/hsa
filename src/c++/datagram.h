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

  struct [[maybe_unused]] TelemetrySecondary
  {
    f32 altitude_barometric;        ///< Высота по барометру                                                `[-1000..1000]`
    f32 altitude_gps;               ///< Высота по GPS                                                      `[-1000..1000]`
    f32 altitude_radio;             ///< Высота по радиовысотомеру                                          `[0..200]`
    f32 gps_course_error;           ///< Погрешность курса по GPS                                           `[-1000..1000]`
    f32 gps_velocity_error;         ///< Погрешность скорости по GPS                                        `[-1000..1000]`
    f32 roll_velocity;              ///< Угловая скорость по оси крена в радианах в секунду                 `[-100..100]`
    f32 roll_velocity_error;        ///< Упр. действие САУ для стабилизации по оси крена                    `[-1..1]`
    f32 pitch_velocity;             ///< Угловая скорость по оси тангажа в радианах в секунду               `[-100..100]`
    f32 pitch_velocity_error;       ///< Упр. действие САУ для стабилизации по оси тангажа                  `[-1..1]`
    f32 yaw_velocity;               ///< Угловая скорость по оси курса в радианах в секунду                 `[-100..100]`
    f32 yaw_velocity_error;         ///< Упр. действие САУ для стабилизации по оси курса                    `[-1..1]`
    f32 position_x;                 ///< Позиция в метрах по оси, напр. на восток, отн. нач. точки          `[-10⁵..10⁵]`
    f32 position_x_error;           ///< Погрешность по позиции по оси, напр. на восток                     `[-1000..1000]`
    f32 position_x_target;          ///< Заданная позиция в м по оси, напр. на восток                       `[-10⁵..10⁵]`
    f32 position_y;                 ///< Позиция в метрах по оси, напр. на север, отн. нач. точки           `[-10⁵..10⁵]`
    f32 position_y_error;           ///< Погрешность по позиции по оси, напр. на север                      `[-1000..1000]`
    f32 position_y_target;          ///< Заданная позиция в м по оси, напр. на север                        `[-10⁵..10⁵]`
    f32 position_z_error;           ///< Погрешность по позиции по оси, напр. вниз                          `[-1000..1000]`
    f32 signal_roll;                ///< Значение сигнала по крену с радиоуправления                        `[-1..1]`
    f32 signal_pitch;               ///< Значение сигнала по тангажу с радиоуправления                      `[-1..1]`
    f32 signal_yaw;                 ///< Значение сигнала по курсу с радиоуправления                        `[-1..1]`
    f32 signal_throttle;            ///< Значение сигнала по газу/шагу с радиоуправления                    `[-1..1]`
    f32 target_roll_velocity;       ///< Заданное знач. в рад/с по гироскопической скорости по оси крена    `[-100..100]`
    f32 target_pitch_velocity;      ///< Заданное знач. в рад/с по гироскопической скорости по оси тангажа  `[-100..100]`
    f32 target_yaw_velocity;        ///< Заданное знач. в рад/с по гироскопической скорости по оси курса    `[-100..100]`
    f32 target_altitude;            ///< Заданное знач. в рад/с по высоте в метрах                          `[-1000..1000]`
    f32 target_roll;                ///< Заданное знач. крена в радианах                                    `[-π..π]`
    f32 target_pitch;               ///< Заданное знач. тангажа в радианах                                  `[-π..π]`
    f32 target_yaw;                 ///< Заданное знач. по курсу в радианах                                 `[0..2π]`
    f32 target_vx;                  ///< Заданное знач. по поперечной скорости в м/с                        `[-100..100]`
    f32 target_vy;                  ///< Заданное знач. по продольной скорости в м/с                        `[-100..100]`
    f32 target_vz;                  ///< Заданное знач. по вертикальной скорости в м/с                      `[-100..100]`
    f32 target_position_x;          ///< Заданное знач. позиции в м по оси, напр. на восток                 `[-100..100]`
    f32 target_position_y;          ///< Заданное знач. позиции в м по оси, напр. на север                  `[-100..100]`
    f32 velocity_x_error;           ///< Погрешность скорости по оси, напр. на восток                       `[-1000..1000]`
    f32 velocity_y_error;           ///< Погрешность скорости по оси, напр. на север                        `[-1000..1000]`
    f32 velocity_z_error;           ///< Погрешность скорости по оси, напр. вниз                            `[-1000..1000]`
  };

  struct Datagram
  {
    UAVMetadata metadata;
    Telemetry telemetry;
  };
} // HSA
