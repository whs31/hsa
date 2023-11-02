//
// Created by whs31 on 11/2/2023.
//

#pragma once

#include <type_traits>
#include <vt45-params.h>
#include "enumutils.h"

namespace HSA
{
  enum class VT45Parameter
  {
    HelicopterName = PARAM_HELINAME
  };

  enum class VT45Class
  {
    Land = CLASS_LAND,
    Heli = CLASS_HELI,
    HeliHW = CLASS_HELIHW,
    Ext = CLASS_EXT
  };

  enum class VT45ClassMax
  {
    Land = CLASS_LAND_MAX,
    Heli = CLASS_HELI_MAX,
    HeliHW = CLASS_HELIHW_MAX,
    Ext = CLASS_EXT_MAX
  };

  enum class VT45OverrideState
  {
    Speed = HELI_OVERRIDER_SPEED,
    Altitude = HELI_OVERRIDER_ALTITUDE,
    VZ = HELI_OVERRIDER_VZ,
    Yaw = HELI_OVERRIDER_YAW,
    Last = HELI_OVERRIDER__LAST
  };
} // HSA
