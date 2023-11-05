//
// Created by whs31 on 03.11.2023.
//

#include "ruavputility.h"
#include "wrapper.h"

namespace ruavp::utility
{
  auto get_uav_id(const VT45::Structures::Header* h) noexcept -> u8 {
    return (h->source bitand 0x0f);
  }
} // ruavp::utility