//
// Created by whs31 on 03.11.2023.
//

#pragma once

#include <functional>
#include <Libra/Global>

struct ruavp_protocol_t;
struct ruavp_header_t;
namespace VT45
{
  namespace Structures
  {
    using Protocol = ruavp_protocol_t;
    using Header = ruavp_header_t;
  } // Structures

  using UavID = u8;
} // VT45

namespace ruavp::utility
{
  using error_function = std::function<void (void)>;

  template<typename T>
  auto any_of_pointers_invalid(VT45::Structures::Protocol* a, const VT45::Structures::Header* b, const T* c) -> bool
  {
    return ((a == nullptr) or (b == nullptr) or (c == nullptr));
  }

  template<typename T>
  auto any_of_pointers_invalid_signaling(VT45::Structures::Protocol* a, const VT45::Structures::Header* b, const T* c, error_function f) -> bool
  {
    auto is_error = any_of_pointers_invalid(a, b, c);
    if(is_error)
      f();
    return is_error;
  }

  auto get_uav_id(const VT45::Structures::Header*) noexcept -> VT45::UavID;
} // ruavp::utility

