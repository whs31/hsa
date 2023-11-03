//
// Created by whs31 on 03.11.2023.
//

#pragma once

#include <Libra/Platform>

#if defined(LIBRA_OS_WINDOWS)
  #if defined(HSA_LIBRARY)
    #define HSA_EXPORT __declspec(dllexport)
  #else
    #define HSA_EXPORT __declspec(dllimport)
  #endif
#else
  #define HSA_EXPORT
#endif
