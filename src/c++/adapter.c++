//
// Created by whs31 on 11/2/2023.
//

#include "adapter.h"
#include <iostream>
#include "config.h"
#include "socket.h"

using std::cout;
using std::endl;

namespace HSA
{
  Adapter::Adapter()
    : m_config(std::make_unique<Config>())
    , m_socket(std::make_unique<Socket>())
  {
    if(not config()->value(Config::VT45ListenPort))
    {
      cout << "Error fetching listen port from config";
      return;
    }

    if(not config()->value(Config::VT45MulticastGroup))
    {
      cout << "Error fetching multicast group from config";
      return;
    }

    socket()->start(std::get<u16>(config()->value(Config::VT45ListenPort).value()));
    socket()->joinMulticastGroup(std::get<string>(config()->value(Config::VT45MulticastGroup).value()));
  }

  Adapter::~Adapter() = default;

  Config* Adapter::config() const { return m_config.get(); }
  Socket* Adapter::socket() const { return m_socket.get(); }
} // HSA