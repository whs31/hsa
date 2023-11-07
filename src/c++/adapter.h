//
// Created by whs31 on 11/2/2023.
//

#pragma once

#include <memory>
#include <string>
#include <asio/io_context.hpp>

using std::string;
using std::unique_ptr;

struct HSA_Telemetry;

namespace HSA
{
  class Config;
  class ISocket;
  class ProtocolParser;
  class Adapter
  {
    public:
      using DataReadyCallback = std::function<void (void)>;

      Adapter(asio::io_context& context, DataReadyCallback callback = {});
      ~Adapter();

      void start();
      void stop();

      [[nodiscard]] Config* config() const;
      [[nodiscard]] ISocket* socket() const;
      [[nodiscard]] ProtocolParser* parser() const;

      [[nodiscard]] HSA_Telemetry telemetryUnmangled() const;
      void setTelemetryUnmangledCallback(DataReadyCallback);

    private:
      void socketRead(const string& data);

    private:
      unique_ptr<Config> m_config;
      unique_ptr<ISocket> m_socket;
      unique_ptr<ProtocolParser> m_protocol_parser;
      DataReadyCallback m_callback;
  };
} // HSA

