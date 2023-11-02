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
        .process_core_ack = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const core_ack_t* d){},
        .process_core_param = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const core_param_t* d){},
        .process_core_message = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const core_message_t* d){},
        .process_helihw_tenso = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const helihw_tenso_t* d){},
        .process_navio_telemetry = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const navio_telemetry_t* d){},
        .process_heli_telemetry = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const heli_telemetry_t* d){},
        .process_heli_route = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const heli_route_t* d){},
        .process_heli_route_point = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const heli_route_point_t* d){},
        .process_heli_status = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const heli_status_t* d){},
        .process_mag_telemetry = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const mag_telemetry_t* d){},
        .process_vip_united_unitdata = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const vip_united_unitdata_t* d){},
        .process_yraw_gps = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const yraw_gps_t* d){},
        .process_zzf_ads1_raw = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzf_ads1_raw_t* d){},
        .process_zzn_servo_feedback = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_servo_feedback_t* d){},
        .process_zzn_brp1 = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_brp1_t* d){},
        .process_zzn_brp2 = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_brp2_t* d){},
        .process_zzn_brp4 = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_brp4_t* d){},
        .process_zzn_engine_telem = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_engine_telem_t* d){},
        .process_zzn_pps_feedback = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzn_pps_feedback_t* d){},
        .process_zzo_bins = +[](ruavp_protocol_t* p, const ruavp_header_t* h, const zzo_bins_t* d){},
        .handle_error = +[](ruavp_protocol_t* p, const void* b, usize s, int reason){},
    };
  }
} // HSA