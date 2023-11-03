//
// Created by whs31 on 11/3/2023.
//

#pragma once

namespace HSA
{
  class ProtocolParser;
  class CLILogger
  {
    public:
      static void LogProtocolCounters(ProtocolParser*);
      static void LogTelemetry(ProtocolParser*);
      static void LogClearLines(int line_count);
  };
} // HSA
