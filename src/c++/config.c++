//
// Created by whs31 on 11/1/2023.
//

#include "config.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <format>
#include "def.h"

namespace fs = std::filesystem;

namespace HSA
{
  const map<Config::ConfigKey, string> EnumerationDictionary = {
    { Config::ConfigKey::VT45IPv4, "vt45_ip" },
    { Config::ConfigKey::VT45Port, "vt45_port" },
    { Config::ConfigKey::VT45ListenPort, "vt45_listen_port" }
  };

  Config::Config()
  {
    this->create();
  }

  auto Config::value(ConfigKey key) const noexcept -> expected<variant<string, u16>, ErrorCode>
  {
    if(not m_values.contains(key))
      return unexpected(ErrorCode::InvalidKey);
    return m_values.at(key);
  }

  void Config::reset() noexcept
  {
    using namespace std::literals;
    using namespace Libra::literals;

    m_values[VT45IPv4] = "192.168.0.13"s;
    m_values[VT45Port] = 4556_u16;
    m_values[VT45ListenPort] = 4557_u16;
    printLn("Config file was reset.");
  }

  auto Config::create() noexcept -> bool
  {
    fs::path path = fs::current_path() / "cfg.json";
    if(exists(path))
    {
      printLn("File exists, loading settings");
      this->load();
      return true;
    }
    std::filesystem::create_directories(path.parent_path());
    std::ofstream ofs(path);

    this->reset();
    printLn("Filling settings file...");
    ofs << "{\n";
    for(usize i = 0; const auto& [key, value] : m_values)
    {
      auto str = holds_alternative<string>(value) ? std::get<string>(value) : std::to_string(std::get<u16>(value));
      printLn("Added key {} with value {}", EnumerationDictionary.at(key), str);
      ofs << std::format("\t\"{}\": \"{}\"", EnumerationDictionary.at(key), str);
      if(i != m_values.size() - 1)
        ofs << ",";
      ofs << "\n";
    }
    ofs << "}\n";
    ofs.close();
    printLn("Settings file filled.");
    return true;
  }

  void Config::load() noexcept
  {

  }
} // HSA