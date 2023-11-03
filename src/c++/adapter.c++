//
// Created by whs31 on 11/2/2023.
//

#include "adapter.h"
#include <iostream>
#include <iomanip>
#include <functional>
#include "config.h"
#include "socket.h"
#include "protocolparser.h"

using std::cout;
using std::endl;

namespace HSA
{
  Adapter::Adapter()
    : m_config(std::make_unique<Config>())
    , m_socket(std::make_unique<Socket>([this](auto&& PH1){ socketRead(std::forward<decltype(PH1)>(PH1)); }))
    , m_protocol_parser(std::make_unique<ProtocolParser>())
  {
    if(not config()->value(Config::VT45ListenPort))
    {
      cout << "Error fetching listen port from config" << endl;
      return;
    }

    if(not config()->value(Config::VT45MulticastGroup))
    {
      cout << "Error fetching multicast group from config" << endl;
      return;
    }

    socket()->start(std::get<u16>(config()->value(Config::VT45ListenPort).value()));
    socket()->joinMulticastGroup(std::get<string>(config()->value(Config::VT45MulticastGroup).value()));
    cout << endl;
  }

  Adapter::~Adapter() = default;

  Config* Adapter::config() const { return m_config.get(); }
  Socket* Adapter::socket() const { return m_socket.get(); }
  ProtocolParser* Adapter::parser() const { return m_protocol_parser.get(); }

  void Adapter::socketRead(string data)
  {
    using std::setw;
    using std::right;
    parser()->decode(data);

    cout << "helihw: " << right << setw(6) << parser()->counter().helihw_tenso << " "
         << "navio: " << right << setw(6) << parser()->counter().navio_telemetry << " "
         << "telemetry: " << right << setw(6) << parser()->counter().heli_telemetry << " "
         << "status: " << right << setw(6) << parser()->counter().heli_status << " "
         << "vuu: " << right << setw(6) << parser()->counter().vip_united_unitdata << " "
         << "mag: " << right << setw(6) << parser()->counter().mag_telemetry
         << "\r";
  }
} // HSA