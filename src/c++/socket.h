//
// Created by whs31 on 11/2/2023.
//

#pragma once

#include <string>
#include <memory>
#include <Libra/Global>

using std::string;
using std::unique_ptr;

class QUdpSocket;

namespace HSA
{
  class Socket
  {
    public:
      Socket();
      ~Socket();

      void start(u16 port) noexcept;
      void stop() noexcept;
      void send(const string& data) noexcept;
      void joinMulticastGroup(const string& ip) noexcept;

    private:
      void read() noexcept;

    private:
      unique_ptr<QUdpSocket> m_socket;
      u16 m_port;
  };
} // HSA


