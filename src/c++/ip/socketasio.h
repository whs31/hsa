//
// Created by whs31 on 04.11.2023.
//

#pragma once

#include "ip/isocket.h"
#include <array>
#include <asio/ip/udp.hpp>

using std::array;

namespace HSA
{
  class SocketASIO : public ISocket
  {
    public:
      explicit SocketASIO(SocketReceiveCallback callback);
      ~SocketASIO();

      void start(u16 port) noexcept override;
      void stop() noexcept override;
      void send(const string& data) noexcept override;
      void joinMulticastGroup(const string& ip) noexcept override;

    protected:
      void read() noexcept override;

    protected:
      SocketReceiveCallback m_callback;
//      asio::io_context m_context;
//      asio::ip::udp::socket m_socket;
//      asio::ip::udp::endpoint m_endpoint;
//      array<char, 1024> m_buffer;
  };
} // HSA

