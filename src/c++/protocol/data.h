//
// Created by whs31 on 11/5/2023.
//

#pragma once

#include <string>
#include <optional>
#include <Libra/Global>
#include "wrapper.h"
#include "ruavputility.h"

using std::string;
using std::optional;

namespace VT45
{
  using UavID = u8;
  struct UAVMetadata
  {
    UavID id;
    string name;
  };

  namespace Structures::Heli
  {
    struct TelemetryOverriders
    {
      u8 override_altitude;
      u8 override_velocity;
      u8 override_yaw;
      u8 override_vz;
    };
  } // Heli::Structures
} // VT45

namespace HSA
{
  struct Data
  {
    VT45::UAVMetadata metadata;
    VT45::Structures::Heli::Telemetry telemetry;
    VT45::Structures::Heli::TelemetryOverriders telemetryOverriders;
    VT45::Structures::Heli::Status status;
    VT45::Structures::MAG::Telemetry magTelemetry;
    optional<VT45::Structures::NavIO::Telemetry> secondaryTelemetry;
  };
} // HSA