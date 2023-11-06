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
      static void LogAddLines(int line_count);
      static void LogClearLines(int line_count);
  };

  namespace Console
  {
    [[maybe_unused]] void EnableConsole();
  }
} // HSA
