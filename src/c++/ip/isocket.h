//
// Created by whs31 on 04.11.2023.
//

#pragma once

#include <string>
#include <memory>
#include <functional>
#include <Libra/Global>

using std::string;
using std::unique_ptr;

namespace HSA
{
  class ISocket
  {
    public:
      using SocketReceiveCallback = std::function<void (string data)>;

      virtual ~ISocket() = default;

      virtual void start(u16 port) = 0;
      virtual void stop() = 0;
      virtual void send(const string& data) = 0;
      virtual void joinMulticastGroup(const string& ip) = 0;

    protected:
      virtual void read() = 0;
  };
} // HSA