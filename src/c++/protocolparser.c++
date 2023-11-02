/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 01.11.23
  *  @copyright Radar-MMS 2023
  */

#include <iostream>
#include "protocolparser.h"
#include "datagram.h"

using std::cout;
using std::cerr;
using std::endl;

#define ruavp_protocol_data ruavp_protocol_t* p, const ruavp_header_t* h

namespace callbacks
{
  void core_ack(ruavp_protocol_data, const core_ack_t* d) {}
  void core_param(ruavp_protocol_data, const core_param_t* d) {}
  void core_message(ruavp_protocol_data, const core_message_t* d) {}
  void helihw_tenso(ruavp_protocol_data, const helihw_tenso_t* d) {}
  void navio_telemetry(ruavp_protocol_data, const navio_telemetry_t* d) {}
  void heli_telemetry(ruavp_protocol_data, const heli_telemetry_t* d) {}
  void heli_route(ruavp_protocol_data, const heli_route_t* d) {}
  void heli_route_point(ruavp_protocol_data, const heli_route_point_t* d) {}
  void heli_status(ruavp_protocol_data, const heli_status_t* d) {}
  void mag_telemetry(ruavp_protocol_data, const mag_telemetry_t* d) {}
  void vip_united_unitdata(ruavp_protocol_data, const vip_united_unitdata_t* d) {}
  void yraw_gps(ruavp_protocol_data, const yraw_gps_t* d) {}
  void zzf_ads1_raw(ruavp_protocol_data, const zzf_ads1_raw_t* d) {}
  void zzn_servo_feedback(ruavp_protocol_data, const zzn_servo_feedback_t* d) {}
  void zzn_brp1(ruavp_protocol_data, const zzn_brp1_t* d) {}
  void zzn_brp2(ruavp_protocol_data, const zzn_brp2_t* d) {}
  void zzn_brp4(ruavp_protocol_data, const zzn_brp4_t* d) {}
  void zzn_engine_telem(ruavp_protocol_data, const zzn_engine_telem_t* d) {}
  void zzn_pps_feedback(ruavp_protocol_data, const zzn_pps_feedback_t* d) {}
  void zzo_bins(ruavp_protocol_data, const zzo_bins_t* d) {}

  void handle_error(ruavp_protocol_t* p, const void* buffer, usize s, int reason) {}
}

namespace HSA
{
  ProtocolParser::ProtocolParser()
    : m_datagram(std::make_unique<Datagram>())
  {
    this->registerCallbacks();
  }

  ProtocolParser::~ProtocolParser() = default;
  Datagram* ProtocolParser::datagram() const { return m_datagram.get(); }

  void ProtocolParser::decode(const string& data) { ruavp_decode_process(&m_protocol, data.c_str(), data.size()); }
  void ProtocolParser::registerCallbacks() noexcept
  {
    m_protocol = {
        .user = this,
        .process_core_ack = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const core_ack_t* d){
          callbacks::core_ack(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_core_param = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const core_param_t* d){
          callbacks::core_param(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_core_message = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const core_message_t* d){
          callbacks::core_message(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_helihw_tenso = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const helihw_tenso_t* d){
          callbacks::helihw_tenso(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_navio_telemetry = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const navio_telemetry_t* d){
          callbacks::navio_telemetry(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_heli_telemetry = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const heli_telemetry_t* d){
          callbacks::heli_telemetry(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_heli_route = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const heli_route_t* d){
          callbacks::heli_route(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_heli_route_point = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const heli_route_point_t* d){
          callbacks::heli_route_point(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_heli_status = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const heli_status_t* d){
          callbacks::heli_status(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_mag_telemetry = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const mag_telemetry_t* d){
          callbacks::mag_telemetry(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_vip_united_unitdata = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const vip_united_unitdata_t* d){
          callbacks::vip_united_unitdata(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_yraw_gps = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const yraw_gps_t* d){
          callbacks::yraw_gps(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_zzf_ads1_raw = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzf_ads1_raw_t* d){
          callbacks::zzf_ads1_raw(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_zzn_servo_feedback = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_servo_feedback_t* d){
          callbacks::zzn_servo_feedback(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_zzn_brp1 = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_brp1_t* d){
          callbacks::zzn_brp1(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_zzn_brp2 = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_brp2_t* d){
          callbacks::zzn_brp2(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_zzn_brp4 = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_brp4_t* d){
          callbacks::zzn_brp4(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_zzn_engine_telem = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_engine_telem_t* d){
          callbacks::zzn_engine_telem(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_zzn_pps_feedback = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_pps_feedback_t* d){
          callbacks::zzn_pps_feedback(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_zzo_bins = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzo_bins_t* d){
          callbacks::zzo_bins(std::forward<decltype(p)>(p),
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
} // HSA