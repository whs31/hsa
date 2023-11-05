//
// Created by whs31 on 11/2/2023.
//

#pragma once

#include <type_traits>
#include "utility/enumutils.h"

extern "C"
{
#include <vt45.h>
#include <vt45-params.h>
}

namespace VT45
{
  enum class Parameter
  {
    HelicopterName = PARAM_HELINAME
  };

  enum class RuavpClass
  {
    Land = CLASS_LAND,
    Heli = CLASS_HELI,
    HeliHW = CLASS_HELIHW,
    Ext = CLASS_EXT,
    LandMax = CLASS_LAND_MAX,
    HeliMax = CLASS_HELI_MAX,
    HeliHWMax = CLASS_HELIHW_MAX,
    ExtMax = CLASS_EXT_MAX
  };

  enum class OverrideState
  {
    Speed = HELI_OVERRIDER_SPEED,
    Altitude = HELI_OVERRIDER_ALTITUDE,
    VZ = HELI_OVERRIDER_VZ,
    Yaw = HELI_OVERRIDER_YAW,
    Last = HELI_OVERRIDER__LAST
  };
}
