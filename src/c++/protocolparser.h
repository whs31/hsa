/**
  *  @file FILE
  *  @author Dmitry Ryazancev
  *  @date 01.11.23
  *  @copyright Radar-MMS 2023
  */

#pragma once

#include <string>
#include <functional>
#include <memory>
#include <vt45.h>
#include <Libra/Global>

using std::string;
using std::unique_ptr;

namespace HSA
{
  struct Datagram;
  class ProtocolParser
  {
    public:
      ProtocolParser();
      ~ProtocolParser();

      [[nodiscard]] Datagram* datagram() const;

      void decode(const string& data);

    private:
      void registerCallbacks() noexcept;

    private:
      ruavp_protocol_t m_protocol;
      unique_ptr<Datagram> m_datagram;
  };
} // HSA

template<typename T>
auto any_of_pointers_invalid(ruavp_protocol_t* a, const ruavp_header_t* b, const T* c) -> bool
{
  return ((a == nullptr) or (b == nullptr) or (c == nullptr));
}
