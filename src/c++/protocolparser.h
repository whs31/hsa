/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 01.11.23
  *  @copyright Radar-MMS 2023
  */

#pragma once

#include <string>
#include <functional>
#include <vt45.h>
#include <Libra/Global>

#define callback_process(T) callback_##T(const T* packet)

using std::string;

namespace RUAVP
{
  template <typename T>
  using Callback = std::function<void (ruavp_protocol_t*, const ruavp_header_t*, const T* packet)>;
}

namespace HSA
{
  class ProtocolParser
  {
    public:
      ProtocolParser();

      void decode(const string& data);

    private:
      void registerCallbacks() noexcept;

      void callback_process(core_ack_t) noexcept;
      void callback_process(core_param_t) noexcept;
      void callback_process(core_message_t) noexcept;
      void callback_process(helihw_tenso_t) noexcept;
      void callback_process(navio_telemetry_t) noexcept;
      void callback_process(heli_telemetry_t) noexcept;
      void callback_process(heli_route_t) noexcept;
      void callback_process(heli_route_point_t) noexcept;
      void callback_process(heli_status_t) noexcept;
      void callback_process(mag_telemetry_t) noexcept;
      void callback_process(vip_united_unitdata_t) noexcept;
      void callback_process(yraw_gps_t) noexcept;
      void callback_process(zzf_ads1_raw_t) noexcept;
      void callback_process(zzn_servo_feedback_t) noexcept;
      void callback_process(zzn_brp1_t) noexcept;
      void callback_process(zzn_brp2_t) noexcept;
      void callback_process(zzn_brp4_t) noexcept;
      void callback_process(zzn_engine_telem_t) noexcept;
      void callback_process(zzn_pps_feedback_t) noexcept;
      void callback_process(zzo_bins_t) noexcept;
      void callback_error_handle(ruavp_protocol_t*, const void* buf, usize size, int reason) noexcept;

    private:
      ruavp_protocol_t m_protocol;
  };
} // HSA
