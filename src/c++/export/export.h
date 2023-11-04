//
// Created by whs31 on 03.11.2023.
//

#pragma once
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-declarations"

#include "hsa.h"

extern "C"
{
//  typedef struct HSA_Telemetry
//  {
//    double latitude;
//  };
}

extern "C" HSA_EXPORT const char* Version() { return PROJECT_VERSION; }

#pragma clang diagnostic pop