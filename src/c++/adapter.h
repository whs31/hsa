//
// Created by whs31 on 11/2/2023.
//

#pragma once

#include <memory>

using std::unique_ptr;

namespace HSA
{
  class Config;
  class Socket;
  class Adapter
  {
    public:
      Adapter();
      ~Adapter();

      [[nodiscard]] Config* config() const;
      [[nodiscard]] Socket* socket() const;

    private:
      unique_ptr<Config> m_config;
      unique_ptr<Socket> m_socket;
  };
} // HSA

