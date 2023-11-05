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

      void start(u16 port) override;
      void stop() override;
      void send(const string& data) override;
      void joinMulticastGroup(const string& ip) override;

    protected:
      void read() override;
      void handleReceiving(const asio::error_code& error, size_t bytes_transferred);

    protected:
      SocketReceiveCallback m_callback;
      array<char, 1024> m_buffer;
      asio::io_context m_context;
      asio::ip::udp::socket m_socket;
      asio::ip::udp::endpoint m_endpoint;
  };
} // HSA

