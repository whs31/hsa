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
#include <unordered_map>
#include <vector>
#include <Libra/Expected>
#include "ruavputility.h"

using std::string;
using std::unique_ptr;
using std::atomic;
using std::unordered_map;
using std::vector;

namespace HSA
{
  struct Data;
  class ProtocolParser
  {
    public:
      enum class HashtableAccessError
      {
        NoSuchKey,
        KeyAlreadyPersistsAtCreation,
        Unknown
      };

      struct Counter
      {
        Counter();

        atomic<usize> core_ack;
        atomic<usize> core_message;
        atomic<usize> core_param;
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

      [[nodiscard]] Data* datagram() const;
      [[nodiscard]] VT45::Structures::Protocol* protocol() const;
      [[nodiscard]] auto counter(VT45::UavID id) -> expected<Counter*, HashtableAccessError>;
      [[nodiscard]] auto addCounter(VT45::UavID id) -> expected<Counter*, HashtableAccessError>;

      [[nodiscard]] auto uavIDList() const -> vector<VT45::UavID>;

      void decode(const string& data) const;

    private:
      void registerCallbacks() noexcept;

    private:
      unique_ptr<VT45::Structures::Protocol> m_protocol;
      unique_ptr<Data> m_datagram;
      unordered_map<VT45::UavID, Counter> m_counters;
      bool m_parse_sec_tel;
  };
} // HSA
