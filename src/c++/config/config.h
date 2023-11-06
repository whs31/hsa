//
// Created by whs31 on 11/1/2023.
//

#pragma once

#include <variant>
#include <string>
#include <map>
#include <bidirectional_map>
#include <Libra/Global>
#include <Libra/Expected>

using std::variant;
using std::string;
using std::map;
using bimap::bidirectional_map;

namespace HSA
{
  class Config
  {
    public:
      enum ConfigKey
      {
        VT45IPv4,
        VT45Port,
        VT45ListenPort,
        VT45MulticastGroup
      };

      enum class ErrorCode
      {
        InvalidKey,
        UnknownError
      };

      Config();

      [[nodiscard]] auto value(ConfigKey) const noexcept -> expected<variant<string, u16>, ErrorCode>;

      #if defined(HSA_STATIC_CONFIG)
      void setValue(ConfigKey key, const variant<string, u16>& value) noexcept;
      void setValueRaw(const char* key, const char* value) noexcept;
      #endif

      void load() noexcept;
      void reset() noexcept;

    private:
      auto create() noexcept -> bool;

    private:
      map<ConfigKey, variant<string, u16>> m_values;
  };
} // HSA

