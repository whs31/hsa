//
// Created by whs31 on 11/3/2023.
//

#include "clilogger.h"
#include "protocolparser.h"
#include "datagram.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::right;
using std::left;
using std::internal;
using std::setw;

constexpr const char* TERM_CLEAN_LAST_LINE = "\033[A\r\033[0K";

namespace HSA
{
  void CLILogger::LogProtocolCounters(ProtocolParser* p)
  {
    cout << left << setw(10) << "HELIHW"    << "\033[0;33m" << setw(8) << p->counter().helihw_tenso         << "\033[0m "
         << left << setw(10) << "NAVIO"     << "\033[0;31m" << setw(8) << p->counter().navio_telemetry      << "\033[0m "
         << left << setw(10) << "HELI TEL"  << "\033[0;33m" << setw(8) << p->counter().heli_telemetry       << "\033[0m "
         << left << setw(10) << "HELI STAT" << "\033[0;33m" << setw(8) << p->counter().heli_status          << "\033[0m "
         << left << setw(10) << "VUD"       << "\033[0;33m" << setw(8) << p->counter().vip_united_unitdata  << "\033[0m "
         << left << setw(10) << "MAG TEL"   << "\033[0;33m" << setw(8) << p->counter().mag_telemetry        << "\033[0m "
         << endl;
  }

  void CLILogger::LogTelemetry(ProtocolParser* p)
  {
    cout << left << setw(10) << "LAT"       << "\033[0;35m" << setw(8) << p->datagram()->telemetry.latitude      << "\033[0m "
         << left << setw(10) << "LON"       << "\033[0;35m" << setw(8) << p->datagram()->telemetry.longitude     << "\033[0m "
         << left << setw(10) << "ALTI"      << "\033[0;35m" << setw(8) << p->datagram()->telemetry.altitude      << "\033[0m "
         << left << setw(10) << "ALTI_ABS"  << "\033[0;35m" << setw(8) << p->datagram()->telemetry.altitude_abs  << "\033[0m "
         << endl;
  }

  void CLILogger::LogClearLines(int line_count)
  {
    for(usize i = 0; i < line_count; ++i)
      cout << TERM_CLEAN_LAST_LINE;
  }
} // HSA