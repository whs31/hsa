//
// Created by whs31 on 11/2/2023.
//

#pragma once

#include <string>
#include <Libra/Global>

using std::string;

namespace HSA
{
  struct UAVMetadata
  {
    u8 id;
    string name;
  };

  struct Datagram
  {
    UAVMetadata metadata;
  };
} // HSA
