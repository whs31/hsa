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

  namespace Structures
  {
    namespace Heli
    {
      struct TelemetryOverriders
      {
        u8 override_altitude;
        u8 override_velocity;
        u8 override_yaw;
        u8 override_vz;
      };
    } // Heli

    namespace HeliHW
    {
      struct TensoStatus
      {
        u8 leftStatus;
        u8 rightStatus;
      };
    } // HeliHW
  } // Structures
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
    VT45::Structures::VIP::UnitedUnitdata vipUnitedUnitdata;
    VT45::Structures::HeliHW::Tenso helihwTenso;
    VT45::Structures::HeliHW::TensoStatus helihwTensoStatus;
    optional<VT45::Structures::NavIO::Telemetry> secondaryTelemetry;
  };
} // HSA