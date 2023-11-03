/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 01.11.23
  *  @copyright Radar-MMS 2023
  */

#pragma once

#include <atomic>
#include <string>
#include <functional>
#include <memory>
#include <Libra/Global>

using std::string;
using std::unique_ptr;
using std::atomic;

struct ruavp_protocol_t;
struct ruavp_header_t;

namespace HSA
{
  struct Datagram;
  class ProtocolParser
  {
    public:
      struct Counter
      {
        Counter();

        atomic<usize> heli_status;
        atomic<usize> heli_telemetry;
        atomic<usize> navio_telemetry;
        atomic<usize> mag_telemetry;
        atomic<usize> vip_united_unitdata;
        atomic<usize> helihw_tenso;
      };

      ProtocolParser();
      ~ProtocolParser();

      [[nodiscard]] bool parseSecondaryTelemetry() const;
      void setSecondaryTelemetryParsing(bool);

      [[nodiscard]] Datagram* datagram() const;
      [[nodiscard]] ruavp_protocol_t* protocol() const;
      [[nodiscard]] Counter& counter();

      void decode(const string& data) const;

    private:
      void registerCallbacks() noexcept;

    private:
      unique_ptr<ruavp_protocol_t> m_protocol;
      unique_ptr<Datagram> m_datagram;
      Counter m_counter;
      bool m_parse_sec_tel;
  };
} // HSA

namespace ruavp::utility
{
  using error_function = std::function<void (void)>;

  template<typename T>
  auto any_of_pointers_invalid(ruavp_protocol_t* a, const ruavp_header_t* b, const T* c) -> bool
  {
    return ((a == nullptr) or (b == nullptr) or (c == nullptr));
  }

  template<typename T>
  auto any_of_pointers_invalid_signaling(ruavp_protocol_t* a, const ruavp_header_t* b, const T* c, error_function f) -> bool
  {
    auto is_error = any_of_pointers_invalid(a, b, c);
    if(is_error)
      f();
    return is_error;
  }
} // ruavp::utility
