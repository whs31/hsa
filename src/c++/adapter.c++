//
// Created by whs31 on 11/2/2023.
//

#include "adapter.h"
#include <functional>
#include "config/config.h"
#include "ip/socket.h"
#include "protocol/protocolparser.h"

#if defined HSA_ENABLE_LOGGING
#include <iostream>
#include "utility/clilogger.h"

using std::cout;
using std::endl;
#endif

namespace HSA
{
  Adapter::Adapter()
    : m_config(std::make_unique<Config>())
    , m_socket(std::make_unique<Socket>([this](auto&& PH1){ socketRead(std::forward<decltype(PH1)>(PH1)); }))
    , m_protocol_parser(std::make_unique<ProtocolParser>())
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

    socket()->start(std::get<u16>(config()->value(Config::VT45ListenPort).value()));
    socket()->joinMulticastGroup(std::get<string>(config()->value(Config::VT45MulticastGroup).value()));

    #if defined HSA_ENABLE_LOGGING
    CLILogger::LogAddLines(5);
    #endif
  }

  Adapter::~Adapter() = default;

  Config* Adapter::config() const { return m_config.get(); }
  Socket* Adapter::socket() const { return m_socket.get(); }
  ProtocolParser* Adapter::parser() const { return m_protocol_parser.get(); }

  void Adapter::socketRead(string data)
  {
    parser()->decode(data);

    #if defined HSA_ENABLE_LOGGING
    CLILogger::LogClearLines(4);
    CLILogger::LogProtocolCounters(parser());
    CLILogger::LogTelemetry(parser());
    #endif
  }
} // HSA