//
// Created by whs31 on 11/3/2023.
//

#include "clilogger.h"
#include "protocolparser.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::right;
using std::left;
using std::internal;
using std::setw;

namespace HSA
{
  void CLILogger::LogProtocolCounters(ProtocolParser* p)
  {
    cout << left << setw(10) << "HELIHW"    << internal << setw(6) << "\033[0;33m" << p->counter().helihw_tenso         << "\033[0m "
         << left << setw(10) << "NAVIO"     << internal << setw(6) << "\033[0;33m" << p->counter().navio_telemetry      << "\033[0m "
         << left << setw(10) << "HELI TEL"  << internal << setw(6) << "\033[0;33m" << p->counter().heli_telemetry       << "\033[0m "
         << left << setw(10) << "HELI STAT" << internal << setw(6) << "\033[0;33m" << p->counter().heli_status          << "\033[0m "
         << left << setw(10) << "VUD"       << internal << setw(6) << "\033[0;33m" << p->counter().vip_united_unitdata  << "\033[0m "
         << left << setw(10) << "MAG TEL"   << internal << setw(6) << "\033[0;33m" << p->counter().mag_telemetry        << "\033[0m "
         << "\r";
      //std::cout << "\033[A\r\033[0K" << std::flush;
  }
} // HSA