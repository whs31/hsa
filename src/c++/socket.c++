//
// Created by whs31 on 11/2/2023.
//

#include "socket.h"
#include <iostream>
#include <QtNetwork/QUdpSocket>

using std::cout;
using std::endl;

namespace HSA
{
  Socket::Socket()
    : m_socket(std::make_unique<QUdpSocket>())
    , m_port(25565)
  {
    Qt::Object::connect(m_socket.get(), &QUdpSocket::readyRead, [this](){ this->read(); });
  }

  Socket::~Socket()
  {
    this->stop();
  }

  void Socket::start(u16 port) noexcept
  {
    cout << "Starting UDP socket on port " << port << endl;
    m_port = port;
    auto err = m_socket->bind(QHostAddress::AnyIPv4, m_port);
    cout << "Socket start" << (err ? "ed successfully" : "up failed") << " on "
         << m_socket->localAddress().toString().toStdString() << endl;
  }

  void Socket::stop() noexcept
  {
    cout << "Closing connection" << endl;
    m_socket->close();
    m_port = 0;
  }

  void Socket::send(const string& data) noexcept
  {

  }

  void Socket::joinMulticastGroup(const string& ip) noexcept
  {
    m_socket->joinMulticastGroup(QHostAddress(Qt::String::fromStdString(ip)));
  }

  void Socket::read() noexcept
  {
    QByteArray buffer(static_cast<isize>(m_socket->pendingDatagramSize()), 0x0);
    QHostAddress host;
    u16 port;
    while(m_socket->hasPendingDatagrams())
      m_socket->readDatagram(buffer.data(), buffer.size(), &host, &port);
    //emit received(buffer);
    cout << "read" << host.toString().toStdString() << " " << port <<  endl;
  }
} // HSA