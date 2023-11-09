//
// Created by whs31 on 11/2/2023.
//

#include "adapter.h"
#include <functional>
#include "config/config.h"
#include "ip/socketasio.h"
#include "protocol/protocolparser.h"
#include "protocol/data.h"
#include "export/dgram.h"

#if defined HSA_STANDALONE
#include "export/export.h"
#endif

#if defined HSA_ENABLE_LOGGING
#include <iostream>
#include <utility>
#include "utility/clilogger.h"

using std::cout;
using std::endl;
using std::cerr;
#endif

namespace HSA
{
  Adapter::Adapter(asio::io_context& context, DataReadyCallback callback)
    : m_config(std::make_unique<Config>())
    , m_protocol_parser(std::make_unique<ProtocolParser>())
    , m_callback(std::move(callback))
  {
    if(not config()->value(Config::VT45ListenPort))
    {
      #if defined HSA_ENABLE_LOGGING
      cout << "Error fetching listen port from config" << endl;
      #endif

      return;
    }

    if(not config()->value(Config::VT45MulticastGroup))
    {
      #if defined HSA_ENABLE_LOGGING
      cout << "Error fetching multicast group from config" << endl;
      #endif

      return;
    }

    m_socket = std::make_unique<SocketASIO>([this](auto&& PH1) { this->socketRead(std::forward<decltype(PH1)>(PH1)); },
                                            context);
    #if defined HSA_ENABLE_LOGGING
    CLILogger::LogAddLines(7);
    #endif
  }

  Adapter::~Adapter() = default;

  Config* Adapter::config() const { return m_config.get(); }
  ISocket* Adapter::socket() const { return m_socket.get(); }
  ProtocolParser* Adapter::parser() const { return m_protocol_parser.get(); }

  void Adapter::socketRead(const string& data)
  {
    parser()->decode(data);
    if(m_callback)
      m_callback();

    #if defined HSA_ENABLE_LOGGING
    CLILogger::LogClearLines(6);
    CLILogger::LogProtocolCounters(parser());
    CLILogger::LogTelemetry(parser());
    #endif
  }

  HSA_Telemetry Adapter::telemetryUnmangled() const
  {
    return {
      .latitude = this->parser()->datagram()->telemetry.latitude,
      .longitude = this->parser()->datagram()->telemetry.longitude,
      .altitude = this->parser()->datagram()->telemetry.altitude,
      .altitude_abs = this->parser()->datagram()->telemetry.altitude_abs,
      .col_pitch = this->parser()->datagram()->telemetry.colpitch,
      .pitch = this->parser()->datagram()->telemetry.pitch,
      .roll = this->parser()->datagram()->telemetry.roll,
      .yaw = this->parser()->datagram()->telemetry.yaw,
      .throttle = this->parser()->datagram()->telemetry.throttle,
      .vx = this->parser()->datagram()->telemetry.vx,
      .vy = this->parser()->datagram()->telemetry.vy,
      .vz = this->parser()->datagram()->telemetry.vz,
      .rpm_engine = static_cast<f32>(this->parser()->datagram()->telemetry.rpm_engine),
      .rpm_rotor = static_cast<f32>(this->parser()->datagram()->telemetry.rpm_rotor),
      .rpm_tail = static_cast<f32>(this->parser()->datagram()->telemetry.rpm_tail),
      .engine_state = this->parser()->datagram()->telemetry.engine_state,
      .autopilot_mode = this->parser()->datagram()->telemetry.mode,
      .altitude_barometric = this->parser()->parseSecondaryTelemetry() ? this->parser()->datagram()->secondaryTelemetry.value().altitude_baro : .0f,
      .altitude_gps = this->parser()->parseSecondaryTelemetry() ? this->parser()->datagram()->secondaryTelemetry.value().altitude_gps : .0f,
      .altitude_radio = this->parser()->parseSecondaryTelemetry() ? this->parser()->datagram()->secondaryTelemetry.value().altitude_radio : .0f,
    };
  }

  void Adapter::setTelemetryUnmangledCallback(Adapter::DataReadyCallback c) { m_callback = std::move(c); }

  void Adapter::start()
  {
    try
    {
      socket()->start(std::get<u16>(config()->value(Config::VT45ListenPort).value()));
      socket()->joinMulticastGroup(std::get<string>(config()->value(Config::VT45MulticastGroup).value()));
    }
    catch(const std::exception& e)
    {
      #if defined HSA_ENABLE_LOGGING
      cerr << e.what() << endl;
      #endif
    }
  }

  void Adapter::stop()
  {
    socket()->stop();
  }
} // HSA