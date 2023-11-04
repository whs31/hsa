//
// Created by whs31 on 11/3/2023.
//

#include "clilogger.h"
#include "protocol/protocolparser.h"
#include "protocol/datagram.h"

#if defined HSA_ENABLE_LOGGING
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::right;
using std::left;
using std::internal;
using std::setw;
#endif

constexpr const char* TERM_CLEAN_LAST_LINE = "\033[A\r\033[0K";

namespace HSA
{
  void CLILogger::LogProtocolCounters(ProtocolParser* p)
  {
    #if defined HSA_ENABLE_LOGGING
    auto uav_ids = p->uavIDList();
    auto counter = p->counter(uav_ids.front()).value();

    cout << left << "UAV ID COUNT: " << "\033[0;33m"  << uav_ids.size()         << "\033[0m"
                 << ", UAV ID USED:" << "\033[0;33m " << p->uavIDList().front() << "\033[0m"
         << "\n";
    cout << left << setw(10) << "HELIHW"    << "\033[0;33m" << setw(8) << counter->helihw_tenso         << "\033[0m "
         << left << setw(10) << "NAVIO"     << "\033[0;31m" << setw(8) << counter->navio_telemetry      << "\033[0m "
         << left << setw(10) << "HELI TEL"  << "\033[0;33m" << setw(8) << counter->heli_telemetry       << "\033[0m "
         << left << setw(10) << "HELI STAT" << "\033[0;33m" << setw(8) << counter->heli_status          << "\033[0m "
         << left << setw(10) << "VUD"       << "\033[0;33m" << setw(8) << counter->vip_united_unitdata  << "\033[0m "
         << left << setw(10) << "MAG TEL"   << "\033[0;33m" << setw(8) << counter->mag_telemetry        << "\033[0m "
         << "\n";
    #endif
  }

  void CLILogger::LogTelemetry(ProtocolParser* p)
  {
    #if defined HSA_ENABLE_LOGGING
    cout << left << setw(10) << "LAT"       << "\033[0;35m" << setw(8) << p->datagram()->telemetry.latitude      << "\033[0m "
         << left << setw(10) << "LON"       << "\033[0;35m" << setw(8) << p->datagram()->telemetry.longitude     << "\033[0m "
         << left << setw(10) << "ALTI"      << "\033[0;35m" << setw(8) << p->datagram()->telemetry.altitude      << "\033[0m "
         << left << setw(10) << "ALTI_ABS"  << "\033[0;35m" << setw(8) << p->datagram()->telemetry.altitude_abs  << "\033[0m "
         << "\n";
    cout << left << setw(10) << "PITCH"     << "\033[0;36m" << setw(8) << p->datagram()->telemetry.pitch         << "\033[0m "
         << left << setw(10) << "ROLL"      << "\033[0;36m" << setw(8) << p->datagram()->telemetry.roll          << "\033[0m "
         << left << setw(10) << "YAW"       << "\033[0;36m" << setw(8) << p->datagram()->telemetry.yaw           << "\033[0m "
         << left << setw(10) << "THROTTLE"  << "\033[0;36m" << setw(8) << p->datagram()->telemetry.throttle      << "\033[0m "
         << "\n";
    #endif
  }

  void CLILogger::LogClearLines(int line_count)
  {
    #if defined HSA_ENABLE_LOGGING
    for(usize i = 0; i < line_count; ++i)
      cout << TERM_CLEAN_LAST_LINE;
    #endif
  }

  void CLILogger::LogAddLines(int line_count)
  {
    #if defined HSA_ENABLE_LOGGING
    for(usize i = 0; i < line_count; ++i)
      cout << "\n";
    #endif
  }
} // HSA