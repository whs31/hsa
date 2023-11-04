//
// Created by whs31 on 04.11.2023.
//

#pragma once

#include "ip/isocket.h"

class QUdpSocket;

namespace HSA
{
  class SocketQtNetwork : public ISocket
  {
    public:
      explicit SocketQtNetwork(SocketReceiveCallback callback);
      ~SocketQtNetwork();

      void start(u16 port) noexcept override;
      void stop() noexcept override;
      void send(const string& data) noexcept override;
      void joinMulticastGroup(const string& ip) noexcept override;

    protected:
      void read() noexcept override;

    protected:
      unique_ptr<QUdpSocket> m_socket;
      u16 m_port;
      SocketReceiveCallback m_callback;
  };
} // HSA

