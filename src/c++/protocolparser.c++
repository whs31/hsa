/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 01.11.23
  *  @copyright Radar-MMS 2023
  */

#include "protocolparser.h"

#define callback_declaration(T) [this](ruavp_protocol_t* p, const ruavp_header_t* h, const T* d) { this->callback_##T(d); }

namespace HSA
{
  ProtocolParser::ProtocolParser()
  {
    this->registerCallbacks();
  }

  void ProtocolParser::decode(const string& data)
  {
    ruavp_decode_process(&m_protocol, data.c_str(), data.size());
  }

  void ProtocolParser::registerCallbacks() noexcept
  {
    RUAVP::Callback<core_ack_t> core_ack = callback_declaration(core_ack_t);
    RUAVP::Callback<core_param_t> core_param = callback_declaration(core_param_t);
    RUAVP::Callback<core_message_t> core_message = callback_declaration(core_message_t);
    RUAVP::Callback<helihw_tenso_t> helihw_tenso = callback_declaration(helihw_tenso_t);
    RUAVP::Callback<navio_telemetry_t> navio_telemetry = callback_declaration(navio_telemetry_t);
    RUAVP::Callback<heli_telemetry_t> heli_telemetry = callback_declaration(heli_telemetry_t);
    RUAVP::Callback<heli_route_t> heli_route = callback_declaration(heli_route_t);
    RUAVP::Callback<heli_route_point_t> heli_route_point = callback_declaration(heli_route_point_t);
    RUAVP::Callback<heli_status_t> heli_status = callback_declaration(heli_status_t);
    RUAVP::Callback<mag_telemetry_t> mag_telemetry = callback_declaration(mag_telemetry_t);
    RUAVP::Callback<vip_united_unitdata_t> vip_united_unitdata = callback_declaration(vip_united_unitdata_t);
    RUAVP::Callback<yraw_gps_t> yraw_gps = callback_declaration(yraw_gps_t);
    RUAVP::Callback<zzf_ads1_raw_t> zzf_ads1_raw = callback_declaration(zzf_ads1_raw_t);
    RUAVP::Callback<zzn_servo_feedback_t> zzn_servo_feedback = callback_declaration(zzn_servo_feedback_t);
    RUAVP::Callback<zzn_brp1_t> zzn_brp1 = callback_declaration(zzn_brp1_t);
    RUAVP::Callback<zzn_brp2_t> zzn_brp2 = callback_declaration(zzn_brp2_t);
    RUAVP::Callback<zzn_brp4_t> zzn_brp4 = callback_declaration(zzn_brp4_t);
    RUAVP::Callback<zzn_engine_telem_t> zzn_engine_telem = callback_declaration(zzn_engine_telem_t);
    RUAVP::Callback<zzn_pps_feedback_t> zzn_pps_feedback = callback_declaration(zzn_pps_feedback_t);
    RUAVP::Callback<zzo_bins_t> zzo_bins = callback_declaration(zzo_bins_t);
    std::function<void (ruavp_protocol_t*, const void*, usize, int)> error_handle =
        [this](ruavp_protocol_t* a, const void* b, usize c, int d) { this->callback_error_handle(a, b, c, d); };

    m_protocol = {
        .user = this,
        .process_core_ack = *core_ack.target<decltype(m_protocol.process_core_ack)>(),
        .process_core_param = *core_param.target<decltype(m_protocol.process_core_param)>(),
        .process_core_message = *core_message.target<decltype(m_protocol.process_core_message)>(),
        .process_helihw_tenso = *helihw_tenso.target<decltype(m_protocol.process_helihw_tenso)>(),
        .process_navio_telemetry = *navio_telemetry.target<decltype(m_protocol.process_navio_telemetry)>(),
        .process_heli_telemetry = *heli_telemetry.target<decltype(m_protocol.process_heli_telemetry)>(),
        .process_heli_route = *heli_route.target<decltype(m_protocol.process_heli_route)>(),
        .process_heli_route_point = *heli_route_point.target<decltype(m_protocol.process_heli_route_point)>(),
        .process_heli_status = *heli_status.target<decltype(m_protocol.process_heli_status)>(),
        .process_mag_telemetry = *mag_telemetry.target<decltype(m_protocol.process_mag_telemetry)>(),
        .process_vip_united_unitdata = *vip_united_unitdata.target<decltype(m_protocol.process_vip_united_unitdata)>(),
        .process_yraw_gps = *yraw_gps.target<decltype(m_protocol.process_yraw_gps)>(),
        .process_zzf_ads1_raw = *zzf_ads1_raw.target<decltype(m_protocol.process_zzf_ads1_raw)>(),
        .process_zzn_servo_feedback = *zzn_servo_feedback.target<decltype(m_protocol.process_zzn_servo_feedback)>(),
        .process_zzn_brp1 = *zzn_brp1.target<decltype(m_protocol.process_zzn_brp1)>(),
        .process_zzn_brp2 = *zzn_brp2.target<decltype(m_protocol.process_zzn_brp2)>(),
        .process_zzn_brp4 = *zzn_brp4.target<decltype(m_protocol.process_zzn_brp4)>(),
        .process_zzn_engine_telem = *zzn_engine_telem.target<decltype(m_protocol.process_zzn_engine_telem)>(),
        .process_zzn_pps_feedback = *zzn_pps_feedback.target<decltype(m_protocol.process_zzn_pps_feedback)>(),
        .process_zzo_bins = *zzo_bins.target<decltype(m_protocol.process_zzo_bins)>(),
        .handle_error = *error_handle.target<decltype(m_protocol.handle_error)>()
    };
  }
} // HSA