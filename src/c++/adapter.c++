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

#if defined HSA_ENABLE_LOGGING
#include <iostream>
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
    , m_callback(callback)
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
      .altitude = this->parser()->datagram()->telemetry.altitude
    };
  }

  void Adapter::setTelemetryUnmangledCallback(Adapter::DataReadyCallback c) { m_callback = std::move(c); }
} // HSA