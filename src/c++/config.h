//
// Created by whs31 on 11/1/2023.
//

#pragma once

#include <variant>
#include <map>
#include <string>
#include <Libra/Global>
#include <Libra/Expected>

using std::variant;
using std::map;
using std::string;

namespace HSA
{
  class Config
  {
    public:
      enum ConfigKey
      {
        VT45IPv4,
        VT45Port,
        VT45ListenPort
      };

      enum class ErrorCode
      {
        InvalidKey,
        UnknownError
      };

      Config();

      [[nodiscard]] auto value(ConfigKey) const noexcept -> expected<variant<string, u16>, ErrorCode>;

      void load() noexcept;
      void reset() noexcept;

    private:
      auto create() noexcept -> bool;

    private:
      map<ConfigKey, variant<string, u16>> m_values;
  };
} // HSA
