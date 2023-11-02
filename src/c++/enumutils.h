//
// Created by whs31 on 02.11.2023.
//

#pragma once

#include <type_traits>

template<typename T>
constexpr typename std::underlying_type<T>::type to_underlying(T t) noexcept
{
  return static_cast<typename std::underlying_type<T>::type>(t);
}
