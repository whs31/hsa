//
// Created by whs31 on 04.11.2023.
//

#include "socketasio.h"
#include <asio/ip/multicast.hpp>
#include <asio/ip/address_v4.hpp>

#if defined(HSA_ENABLE_LOGGING)
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
#endif

namespace HSA
{
  SocketASIO::SocketASIO(ISocket::SocketReceiveCallback callback, asio::io_context& context)
    : m_callback(std::move(callback))
    , m_socket(context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 1110))
    , m_endpoint(m_socket.local_endpoint())
  {}

  SocketASIO::~SocketASIO()
  {
    this->SocketASIO::stop();
  }

  void SocketASIO::start(u16 port)
  {
    this->stop();

    #if defined HSA_ENABLE_LOGGING
    cout << "Starting UDP socket on port " << port << endl;
    #endif

    m_endpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), port);
    m_socket.open(m_endpoint.protocol());
    m_socket.bind(m_endpoint);
    this->read();

    #if defined HSA_ENABLE_LOGGING
    cout << "Socket started on " << m_socket.local_endpoint().address().to_string()
         << ":" << m_socket.local_endpoint().port() << endl;
    #endif
  }

  void SocketASIO::stop()
  {
    m_socket.close();
    //m_socket.shutdown(asio::socket_base::shutdown_type::shutdown_both);
    m_endpoint = {};
    #if defined HSA_ENABLE_LOGGING
    cout << "Closing connection" << endl;
    #endif
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
      m_callback(std::string(m_buffer.data(), bytes_transferred));
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