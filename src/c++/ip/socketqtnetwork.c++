//
// Created by whs31 on 04.11.2023.
//
#if (0)
#include "socketqtnetwork.h"
#include <utility>
#include <QtNetwork/QUdpSocket>

#if defined HSA_ENABLE_LOGGING
#include <iostream>

using std::cout;
using std::endl;
#endif

namespace HSA
{
  SocketQtNetwork::SocketQtNetwork(ISocket::SocketReceiveCallback callback)
    : m_socket(std::make_unique<QUdpSocket>())
    , m_port(25565)
    , m_callback(std::move(callback))
  {
    Qt::Object::connect(m_socket.get(), &QUdpSocket::readyRead, [this](){ this->read(); });
  }

  SocketQtNetwork::~SocketQtNetwork()
  {
    this->stop();
  }

  void SocketQtNetwork::start(u16 port)
  {
    #if defined HSA_ENABLE_LOGGING
    cout << "Starting UDP socket on port " << port << endl;
    #endif

    m_port = port;
    auto err = m_socket->bind(QHostAddress::AnyIPv4, m_port);

    #if defined HSA_ENABLE_LOGGING
    cout << "Socket start" << (err ? "ed successfully" : "up failed") << " on "
         << m_socket->localAddress().toString().toStdString() << ":" << m_port << endl;
    #endif
  }

  void SocketQtNetwork::stop()
  {
    #if defined HSA_ENABLE_LOGGING
    cout << "Closing connection" << endl;
    #endif

    m_socket->close();
    m_port = 0;
  }

  void SocketQtNetwork::send(const string& data)
  {
    // @todo send function!
  }

  void SocketQtNetwork::joinMulticastGroup(const string& ip)
  {
    m_socket->joinMulticastGroup(QHostAddress(Qt::String::fromStdString(ip)));
  }

  void SocketQtNetwork::read()
  {
    Qt::ByteArray buffer(static_cast<isize>(m_socket->pendingDatagramSize()), 0x0);
    QHostAddress host;
    u16 port;
    while(m_socket->hasPendingDatagrams())
      m_socket->readDatagram(buffer.data(), buffer.size(), &host, &port);
    m_callback(buffer.toStdString());
  }
} // HSA
#endif