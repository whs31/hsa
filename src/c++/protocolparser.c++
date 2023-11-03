/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 01.11.23
  *  @copyright Radar-MMS 2023
  */

#include <iostream>
#include <vt45.h>
#include "protocolparser.h"
#include "datagram.h"
#include "parameters.h"

using std::cout;
using std::cerr;
using std::endl;

#define ruavp_protocol_data ruavp_protocol_t* p, const ruavp_header_t* h

namespace callbacks
{
  /* NOLINTNEXTLINE(cppcoreguidelines-interfaces-global-init) */
  [[maybe_unused]] const ruavp::utility::error_function ErrorFunction = [](){ cerr << "Invalid pointer received!" << endl; };

  /* void core_ack(ruavp_protocol_data, const core_ack_t* d) {}                         */

  void core_param(ruavp_protocol_data, const core_param_t* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;
    auto self = static_cast<HSA::ProtocolParser*>(p->user);
    if(d->id == to_underlying(HSA::VT45Parameter::HelicopterName))
      self->datagram()->metadata = {
          .id = static_cast<u8>(d->id),
          .name = string(reinterpret_cast<const char*>(d->data))
      };
  }

  /* void core_message(ruavp_protocol_data, const core_message_t* d) {}                 */
  /* void helihw_tenso(ruavp_protocol_data, const helihw_tenso_t* d) {}                 */

  void navio_telemetry(ruavp_protocol_data, const navio_telemetry_t* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;
    auto self = static_cast<HSA::ProtocolParser*>(p->user);
    if(not self->parseSecondaryTelemetry())
      return;

    self->counter().navio_telemetry++;
    self->datagram()->secondaryTelemetry.value() = {
      .altitude_barometric = d->altitude_baro,
      .altitude_gps = d->altitude_gps,
      .altitude_radio = d->altitude_radio,
      .gps_course_error = d->gps_course_variance,
      .gps_velocity_error = d->gps_speed_variance,
      .roll_velocity = d->gx,
      .roll_velocity_error = d->gx_err,
      .pitch_velocity = d->gy,
      .pitch_velocity_error = d->gy_err,
      .yaw_velocity = d->gz,
      .yaw_velocity_error = d->gz_err,
      .position_x = d->x,
      .position_x_error = d->pos_variance_x,
      .position_x_target = d->x_dst,
      .position_y = d->y,
      .position_y_error = d->pos_variance_y,
      .position_y_target = d->y_dst,
      .position_z_error = d->pos_variance_z,
      .signal_roll = d->rc_roll,
      .signal_pitch = d->rc_pitch,
      .signal_yaw = d->rc_yaw,
      .signal_throttle = d->rc_throttle,
      .target_roll_velocity = d->sp_gx,
      .target_pitch_velocity = d->sp_gy,
      .target_yaw_velocity = d->sp_gz,
      .target_altitude = d->sp_height,
      .target_roll = d->sp_roll,
      .target_pitch = d->sp_pitch,
      .target_yaw = d->sp_yaw,
      .target_vx = d->sp_vx,
      .target_vy = d->sp_vy,
      .target_vz = d->sp_vz,
      .target_position_x = d->sp_x,
      .target_position_y = d->sp_y,
      .velocity_x_error = d->vel_variance_x,
      .velocity_y_error = d->vel_variance_y,
      .velocity_z_error = d->vel_variance_z
    };
  }

  void heli_telemetry(ruavp_protocol_data, const heli_telemetry_t* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;
    if(not (h->source bitand to_underlying(HSA::VT45Class::Heli)))
      return;
    auto self = static_cast<HSA::ProtocolParser*>(p->user);
    /* @todo
     * QString uavName = core->m_uavNames[uavId];
     * if (!uavName.size())
     *     core->sendGetParam(uavId, PARAM_HELINAME);
     */

    self->counter().heli_telemetry++;
    self->datagram()->telemetry = {
        .latitude = d->latitude,
        .longitude = d->longitude,
        .latitude_d = d->dlatitude,
        .longitude_d = d->longitude,
        .altitude = d->altitude,
        .altitude_abs = d->altitude_abs,
        .altitude_d = d->daltitude,
        .timestamp = d->ts,
        .acceleration_x = d->ax,
        .acceleration_y = d->ay,
        .acceleration_z = d->az,
        .col_pitch = d->colpitch,
        .pitch = d->pitch,
        .roll = d->roll,
        .yaw = d->yaw,
        .target_altitude = d->target_altitude,
        .target_speed = d->target_speed,
        .throttle = d->throttle,
        .vx = d->vx,
        .vy = d->vy,
        .vz = d->vz,
        .route_point = d->route_point,
        .route = d->route,
        .rpm_engine = d->rpm_engine,
        .rpm_engine2 = d->rpm_engine,
        .rpm_rotor = d->rpm_rotor,
        .rpm_tail = d->rpm_tail,
        .engine_state = d->engine_state,
        .mode = d->mode,
        .overriders_state = d->overriders_state,
        .override_altitude = static_cast<u8>((d->overriders_state bitand (1 << to_underlying(HSA::VT45OverrideState::Altitude)))),
        .override_velocity = static_cast<u8>((d->overriders_state bitand (1 << to_underlying(HSA::VT45OverrideState::Speed)))),
        .override_yaw = static_cast<u8>((d->overriders_state bitand (1 << to_underlying(HSA::VT45OverrideState::Yaw)))),
        .override_vz = static_cast<u8>((d->overriders_state bitand (1 << to_underlying(HSA::VT45OverrideState::VZ))))
    };
  }

  /* void heli_route(ruavp_protocol_data, const heli_route_t* d) {}                             */
  /* void heli_route_point(ruavp_protocol_data, const heli_route_point_t* d) {}                 */
  /* void heli_status(ruavp_protocol_data, const heli_status_t* d) {}                           */
  /* void mag_telemetry(ruavp_protocol_data, const mag_telemetry_t* d) {}                       */
  /* void vip_united_unitdata(ruavp_protocol_data, const vip_united_unitdata_t* d) {}           */
  /* void yraw_gps(ruavp_protocol_data, const yraw_gps_t* d) {}                                 */
  /* void zzf_ads1_raw(ruavp_protocol_data, const zzf_ads1_raw_t* d) {}                         */
  /* void zzn_servo_feedback(ruavp_protocol_data, const zzn_servo_feedback_t* d) {}             */
  /* void zzn_brp1(ruavp_protocol_data, const zzn_brp1_t* d) {}                                 */
  /* void zzn_brp2(ruavp_protocol_data, const zzn_brp2_t* d) {}                                 */
  /* void zzn_brp4(ruavp_protocol_data, const zzn_brp4_t* d) {}                                 */
  /* void zzn_engine_telem(ruavp_protocol_data, const zzn_engine_telem_t* d) {}                 */
  /* void zzn_pps_feedback(ruavp_protocol_data, const zzn_pps_feedback_t* d) {}                 */
  /* void zzo_bins(ruavp_protocol_data, const zzo_bins_t* d) {}                                 */

  void handle_error(ruavp_protocol_t* p, const void* buffer, usize s, int reason) {}
}

namespace HSA
{
  ProtocolParser::ProtocolParser()
    : m_datagram(std::make_unique<Datagram>())
    , m_protocol(std::make_unique<ruavp_protocol_t>())
    , m_parse_sec_tel(false)
  {
    this->registerCallbacks();
  }

  ProtocolParser::~ProtocolParser() = default;

  bool ProtocolParser::parseSecondaryTelemetry() const { return m_parse_sec_tel; }
  void ProtocolParser::setSecondaryTelemetryParsing(bool x) {
    m_parse_sec_tel = x;
    this->datagram()->secondaryTelemetry.reset();
  }

  ProtocolParser::Counter& ProtocolParser::counter() { return m_counter; }
  Datagram* ProtocolParser::datagram() const { return m_datagram.get(); }
  ruavp_protocol_t* ProtocolParser::protocol() const { return m_protocol.get(); }

  void ProtocolParser::decode(const string& data) const { ruavp_decode_process(protocol(), data.c_str(), data.size()); }
  void ProtocolParser::registerCallbacks() noexcept
  {
    *protocol() = {
        .user = this,
        .process_core_param = +[](ruavp_protocol_data, const core_param_t* d){
          callbacks::core_param(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_navio_telemetry = +[](ruavp_protocol_data, const navio_telemetry_t* d){
          callbacks::navio_telemetry(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_heli_telemetry = +[](ruavp_protocol_data, const heli_telemetry_t* d){
          callbacks::heli_telemetry(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .handle_error = +[](ruavp_protocol_t* p, const void* b, usize s, int reason){
          callbacks::handle_error(
              std::forward<decltype(p)>(p),
              std::forward<decltype(b)>(b),
              std::forward<decltype(s)>(s),
              std::forward<decltype(reason)>(reason));
          },
    };
  }

  ProtocolParser::Counter::Counter()
    : heli_status(0)
    , heli_telemetry(0)
    , navio_telemetry(0)
    , mag_telemetry(0)
    , vip_united_unitdata(0)
    , helihw_tenso(0)
  {}
} // HSA