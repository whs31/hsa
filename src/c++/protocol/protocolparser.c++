/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 01.11.23
  *  @copyright Radar-MMS 2023
  */

#include "protocolparser.h"
#include "data.h"
#include "parameters.h"

#include <ranges>
#include <Libra/Platform>

#if defined HSA_ENABLE_LOGGING
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#endif

using PROTO = VT45::Structures::Protocol*;
using HDR = const VT45::Structures::Header*;

namespace callbacks
{
  /* NOLINTNEXTLINE(cppcoreguidelines-interfaces-global-init) */
  [[maybe_unused]] const ruavp::utility::error_function ErrorFunction = [](){
    #if defined HSA_ENABLE_LOGGING
    cerr << "Invalid pointer received!" << endl;
    #endif
  };

  /* void core_ack(ruavp_protocol_data, const core_ack_t* d) {}                         */

  void core_param(PROTO p, HDR h, const VT45::Structures::Core::Parameter* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;

    auto self = ruavp::utility::get_user(p);
    if(d->id == to_underlying(VT45::Parameter::HelicopterName))
      self->datagram()->metadata = {
          .id = static_cast<u8>(d->id),
          .name = string(reinterpret_cast<const char*>(d->data))
      };
  }

  /* void core_message(ruavp_protocol_data, const core_message_t* d) {}                 */

  void helihw_tenso(PROTO p, HDR h, const VT45::Structures::HeliHW::Tenso* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;
    if(not (h->source bitand to_underlying(VT45::RuavpClass::Heli)))
      return;

    auto self = ruavp::utility::get_user(p);
    auto id = ruavp::utility::get_uav_id(h);
    auto cnt = self->counter(id);
    if(cnt.has_value())
      cnt.value()->helihw_tenso++;
    else
      self->addCounter(id).value()->helihw_tenso++;
    self->datagram()->helihwTenso = *(d);
    self->datagram()->helihwTensoStatus = {
      .leftStatus = static_cast<u8>((d->__bit_1 bitand 0x01)),
      .rightStatus = static_cast<u8>((d->__bit_1 bitand 0x02))
    };
  }

  void navio_telemetry(PROTO p, HDR h, const VT45::Structures::NavIO::Telemetry* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;

    auto self = ruavp::utility::get_user(p);
    if(not self->parseSecondaryTelemetry())
      return;

    auto id = ruavp::utility::get_uav_id(h);
    auto cnt = self->counter(id);
    if(cnt.has_value())
      cnt.value()->navio_telemetry++;
    else
      self->addCounter(id).value()->navio_telemetry++;

    self->datagram()->secondaryTelemetry.value() = *(d);
  }

  void heli_telemetry(PROTO p, HDR h, const VT45::Structures::Heli::Telemetry* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;
    if(not (h->source bitand to_underlying(VT45::RuavpClass::Heli)))
      return;

    auto self = ruavp::utility::get_user(p);
    /* @todo
     * QString uavName = core->m_uavNames[uavId];
     * if (!uavName.size())
     *     core->sendGetParam(uavId, PARAM_HELINAME);
     */

    auto id = ruavp::utility::get_uav_id(h);
    auto cnt = self->counter(id);
    if(cnt.has_value())
      cnt.value()->heli_telemetry++;
    else
      self->addCounter(id).value()->heli_telemetry++;

    self->datagram()->telemetry = *(d);
    self->datagram()->telemetryOverriders = {
      .override_altitude = static_cast<u8>((d->overriders_state bitand (1 << to_underlying(VT45::OverrideState::Altitude)))),
      .override_velocity = static_cast<u8>((d->overriders_state bitand (1 << to_underlying(VT45::OverrideState::Speed)))),
      .override_yaw = static_cast<u8>((d->overriders_state bitand (1 << to_underlying(VT45::OverrideState::Yaw)))),
      .override_vz = static_cast<u8>((d->overriders_state bitand (1 << to_underlying(VT45::OverrideState::VZ))))
    };
  }

  /* void heli_route(ruavp_protocol_data, const heli_route_t* d) {}                             */
  /* void heli_route_point(ruavp_protocol_data, const heli_route_point_t* d) {}                 */

  void heli_status(PROTO p, HDR h, const VT45::Structures::Heli::Status* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;
    if(not(h->source bitand to_underlying(VT45::RuavpClass::Heli)))
      return;

    auto self = ruavp::utility::get_user(p);
    auto id = ruavp::utility::get_uav_id(h);
    auto cnt = self->counter(id);
    if(cnt.has_value())
      cnt.value()->heli_status++;
    else
      self->addCounter(id).value()->heli_status++;

    self->datagram()->status = *(d);
  }

  void mag_telemetry(PROTO p, HDR h, const VT45::Structures::MAG::Telemetry* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;

    auto self = ruavp::utility::get_user(p);
    auto id = ruavp::utility::get_uav_id(h);
    auto cnt = self->counter(id);
    if(cnt.has_value())
      cnt.value()->mag_telemetry++;
    else
      self->addCounter(id).value()->mag_telemetry++;
    self->datagram()->magTelemetry = *(d);
  }

  void vip_united_unitdata(PROTO p, HDR h, const VT45::Structures::VIP::UnitedUnitdata* d)
  {
    if(ruavp::utility::any_of_pointers_invalid_signaling(p, h, d, ErrorFunction))
      return;

    auto self = ruavp::utility::get_user(p);
    auto id = ruavp::utility::get_uav_id(h);
    auto cnt = self->counter(id);
    if(cnt.has_value())
      cnt.value()->vip_united_unitdata++;
    else
      self->addCounter(id).value()->vip_united_unitdata++;
    self->datagram()->vipUnitedUnitdata = *(d);
  }
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
    : m_datagram(std::make_unique<Data>())
    , m_protocol(std::make_unique<ruavp_protocol_t>())
    , m_parse_sec_tel(true)
  {
    this->setSecondaryTelemetryParsing(true);
    this->registerCallbacks();
  }

  ProtocolParser::~ProtocolParser() = default;

  bool ProtocolParser::parseSecondaryTelemetry() const { return m_parse_sec_tel; }
  void ProtocolParser::setSecondaryTelemetryParsing(bool x) {
    m_parse_sec_tel = x;
    if(x)
      this->datagram()->secondaryTelemetry.emplace();
    else
      this->datagram()->secondaryTelemetry.reset();
  }

  // I guarantee that this pointer is valid!
  auto ProtocolParser::counter(VT45::UavID id) -> expected<Counter*, HashtableAccessError>
  {
    if(not m_counters.contains(id))
      return unexpected(HashtableAccessError::NoSuchKey);
    return &(m_counters[id]);
  }

  auto ProtocolParser::addCounter(VT45::UavID id) -> expected<Counter*, HashtableAccessError>
  {
    if(m_counters.contains(id))
      return unexpected(HashtableAccessError::KeyAlreadyPersistsAtCreation);
    m_counters.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple());
    return counter(id);
  }

  auto ProtocolParser::uavIDList() const -> vector<VT45::UavID>
  {
    #if defined(LIBRA_OS_WINDOWS)
    auto key_view = std::views::keys(m_counters);
    return { key_view.begin(), key_view.end() };
    #else
    vector<ruavp::utility::UavID> ret;
    for(const auto& [key, _] : m_counters)
      ret.push_back(key);
    return ret;
    #endif
  }

  Data* ProtocolParser::datagram() const { return m_datagram.get(); }
  VT45::Structures::Protocol* ProtocolParser::protocol() const { return m_protocol.get(); }

  void ProtocolParser::decode(const string& data) const { ruavp_decode_process(protocol(), data.c_str(), data.size()); }
  void ProtocolParser::registerCallbacks() noexcept
  {
    *protocol() = {
        .user = this,
        .process_core_param = +[](PROTO p, HDR h, const VT45::Structures::Core::Parameter* d){
          callbacks::core_param(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_navio_telemetry = +[](PROTO p, HDR h, const VT45::Structures::NavIO::Telemetry* d){
          callbacks::navio_telemetry(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_heli_telemetry = +[](PROTO p, HDR h, const VT45::Structures::Heli::Telemetry* d){
          callbacks::heli_telemetry(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .process_heli_status = +[](PROTO p, HDR h, const VT45::Structures::Heli::Status* d){
          callbacks::heli_status(
              std::forward<decltype(p)>(p),
              std::forward<decltype(h)>(h),
              std::forward<decltype(d)>(d));
          },
        .handle_error = +[](PROTO p, const void* b, usize s, int reason){
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
