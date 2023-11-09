//
// Created by whs31 on 11/1/2023.
//

#include "export/export.h"

#include <iostream>
#include <thread>
#include <system_error>

void readyRead()
{
  auto a = Read();
  std::cout << a.latitude << " " << a.longitude << " " << a.altitude << " " << a.altitude_abs << " "
            << a.col_pitch << " " << a.pitch << " " << a.roll << " " << a.yaw << " " << a.throttle << " "
            << a.vx << " " << a.vy << " " << a.vz << " " << a.rpm_engine << " " << a.rpm_rotor << " "
            << a.rpm_tail << " " << a.engine_state << " " << a.autopilot_mode
            << " " << a.altitude_barometric << " " << a.altitude_gps << " " << a.altitude_radio
            << std::endl;
}

int main(int argc, char** argv)
{
  #if defined HSA_ENABLE_LOGGING
  std::cout << "HSA version " << PROJECT_VERSION << " started." << std::endl;
  #endif

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  start:
    Run(readyRead);
    std::cin.get();
    Stop();
    char c;
    std::cin.get(c);
    if(c == 'b')
      goto exit;
    goto start;
  exit:
    return EXIT_SUCCESS;
}