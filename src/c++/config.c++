//
// Created by whs31 on 11/1/2023.
//

#include "config.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;
using std::cout;
using std::endl;

namespace HSA
{
  const map<Config::ConfigKey, string> EnumerationDictionary = {
    { Config::ConfigKey::VT45IPv4, "vt45_ip" },
    { Config::ConfigKey::VT45Port, "vt45_port" },
    { Config::ConfigKey::VT45ListenPort, "vt45_listen_port" }
  };

  const map<string, Config::ConfigKey> EnumerationInverseDictionary = {
    { "vt45_ip", Config::ConfigKey::VT45IPv4 },
    { "vt45_port", Config::ConfigKey::VT45Port },
    { "vt45_listen_port", Config::ConfigKey::VT45ListenPort }
  };

  constexpr const char* CFG_FILENAME = "cfg.json";

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
    cout << "Config file was reset" << endl;
  }

  auto Config::create() noexcept -> bool
  {
    fs::path path = fs::current_path() / CFG_FILENAME;
    if(exists(path))
    {
      cout << "File exists, loading settings" << endl;
      this->load();
      return true;
    }
    std::filesystem::create_directories(path.parent_path());
    std::ofstream ofs(path);

    this->reset();
    printLn("Filling settings file");
    ofs << "{\n";
    for(usize i = 0; const auto& [key, value] : m_values)
    {
      auto str = holds_alternative<string>(value) ? std::get<string>(value) : std::to_string(std::get<u16>(value));
      cout << "Added key" << EnumerationDictionary.at(key) << "with value" << str << endl;
      ofs << "\t\"" << EnumerationDictionary.at(key) << "\": \"" << str << "\"";
      if(i != m_values.size() - 1)
        ofs << ",";
      ofs << "\n";
      ++i;
    }
    ofs << "}\n";
    ofs.close();
    cout << "Settings file filled" << endl;
    this->load();
    return true;
  }

  void Config::load() noexcept
  {
    fs::path path = fs::current_path() / CFG_FILENAME;
    cout << "Loading settings from" << CFG_FILENAME << endl;
    std::ifstream ifs(path);
    string line_buffer;
    while(std::getline(ifs, line_buffer))
    {
      auto semicolon = line_buffer.find(':');
      if(semicolon == string::npos)
        continue;
      string key = line_buffer.substr(0, semicolon);
      string value = line_buffer.substr(semicolon + 1, line_buffer.size());
      cout << key << endl;
      cout << value << endl;
    }
  }
} // HSA