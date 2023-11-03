//
// Created by whs31 on 03.11.2023.
//

#pragma once

#include <functional>
#include <Libra/Global>

struct ruavp_protocol_t;
struct ruavp_header_t;

namespace ruavp::utility
{
  using error_function = std::function<void (void)>;
  using UavID = u8;

  template<typename T>
  auto any_of_pointers_invalid(ruavp_protocol_t* a, const ruavp_header_t* b, const T* c) -> bool
  {
    return ((a == nullptr) or (b == nullptr) or (c == nullptr));
  }

  template<typename T>
  auto any_of_pointers_invalid_signaling(ruavp_protocol_t* a, const ruavp_header_t* b, const T* c, error_function f) -> bool
  {
    auto is_error = any_of_pointers_invalid(a, b, c);
    if(is_error)
      f();
    return is_error;
  }

  auto get_uav_id(const ruavp_header_t*) noexcept -> UavID;
} // ruavp::utility

