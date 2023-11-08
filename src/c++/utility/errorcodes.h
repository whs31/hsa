//
// Created by whs31 on 11/8/2023.
//

#pragma once

#include <system_error>
#include <string>

using std::string;

namespace HSA
{
  enum class ErrorCode
  {
    NoSuchKey = 10,
    KeyAlreadyPersistsAtCreation = 11,
    UnknownError = 0xFFFF
  };

  class hsa_error_category_impl : public std::error_category
  {
    public:
      [[nodiscard]] inline const char* name() const noexcept override { return "HSA"; }

      [[nodiscard]] inline string message(int ev) const override
      {
        switch (static_cast<ErrorCode>(ev))
        {
          case ErrorCode::NoSuchKey: return "No such key";
          case ErrorCode::KeyAlreadyPersistsAtCreation: return "Key already persists at creation";
          case ErrorCode::UnknownError: [[fallthrough]];
          default: return "Unknown error";
        }
      }

      [[nodiscard]] inline std::error_condition default_error_condition(int ev) const noexcept override;
  };

  inline const std::error_category& hsa_error_category()
  {
    static hsa_error_category_impl instance;
    return instance;
  }

  inline std::error_condition make_error_condition(ErrorCode ev) noexcept
  {
    return { static_cast<int>(ev), hsa_error_category() };
  }

  inline std::error_code make_error_code(ErrorCode ev) noexcept
  {
    return { static_cast<int>(ev), hsa_error_category() };
  }

  inline std::error_condition hsa_error_category_impl::default_error_condition(int ev) const noexcept
  {
    return { ev, *this };
  }
} // HSA

namespace std
{
  template<> struct is_error_code_enum<HSA::ErrorCode> : public true_type
  {
    static const bool value = true;
  };
} // std
