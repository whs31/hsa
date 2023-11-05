//
// Created by whs31 on 04.11.2023.
//

#include "socketasio.h"

#if defined(HSA_ENABLE_LOGGING)
#include <iostream>
#include <asio/ip/multicast.hpp>
#include <asio/ip/address_v4.hpp>

using std::cerr;
using std::cout;
using std::endl;
#endif

namespace HSA
{
  SocketASIO::SocketASIO(ISocket::SocketReceiveCallback callback)
    : m_callback(std::move(callback))
    , m_context()
    , m_socket(m_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 1110))
    , m_endpoint(m_socket.local_endpoint())
  {}

  void SocketASIO::start(u16 port)
  {
    m_endpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), port);
    m_context.run();
    try
    {
      m_socket.open(m_endpoint.protocol());
      m_socket.bind(m_endpoint);
      this->read();
    }
    catch(const std::exception& e)
    {
      cerr << e.what() << endl;
    }
  }

  void SocketASIO::stop()
  {
    m_socket.close();
    m_context.stop();
    m_endpoint = {};
  }

  void SocketASIO::send(const string& data)
  {
    // TODO
  }

  void SocketASIO::joinMulticastGroup(const string& ip)
  {
    m_socket.set_option(asio::ip::multicast::join_group(asio::ip::make_address_v4(ip)));
  }

  void SocketASIO::handleReceiving(const asio::error_code& error, size_t bytes_transferred)
  {
    if(not error)
    {
      m_callback(std::string(m_buffer.data(), bytes_transferred));
    }
    this->read();
  }

  void SocketASIO::read()
  {
    m_socket.async_receive_from(asio::buffer(m_buffer), m_endpoint, [this](auto&& PH1, auto&& PH2)
    { this->handleReceiving(std::forward<decltype(PH1)>(PH1),
                            std::forward<decltype(PH2)>(PH2));
    });
  }
} // HSA