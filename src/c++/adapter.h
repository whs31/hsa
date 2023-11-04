//
// Created by whs31 on 11/2/2023.
//

#pragma once

#include <memory>
#include <string>

using std::string;
using std::unique_ptr;

namespace HSA
{
  class Config;
  class Socket;
  class ProtocolParser;
  class Adapter
  {
    public:
      Adapter();
      ~Adapter();

      [[nodiscard]] Config* config() const;
      [[nodiscard]] Socket* socket() const;
      [[nodiscard]] ProtocolParser* parser() const;

    private:
      void socketRead(const string& data);

    private:
      unique_ptr<Config> m_config;
      unique_ptr<Socket> m_socket;
      unique_ptr<ProtocolParser> m_protocol_parser;
  };
} // HSA

