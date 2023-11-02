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
  const bidirectional_map<Config::ConfigKey, string> EnumerationDictionary = {
    { Config::ConfigKey::VT45IPv4, "vt45_ip" },
    { Config::ConfigKey::VT45Port, "vt45_port" },
    { Config::ConfigKey::VT45ListenPort, "vt45_listen_port" },
    { Config::ConfigKey::VT45MulticastGroup, "vt45_multicast_group" }
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
    m_values[VT45MulticastGroup] = "224.0.0.1";
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
    cout << "Filling settings file" << endl;
    ofs << "{\n";
    for(usize i = 0; const auto& [key, value] : m_values)
    {
      auto str = holds_alternative<string>(value) ? std::get<string>(value) : std::to_string(std::get<u16>(value));
      cout << "\tAdded key " << EnumerationDictionary.at(key) << " with value " << str << endl;
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
    cout << "Loading settings from " << CFG_FILENAME << endl;
    std::ifstream ifs(path);
    string line_buffer;
    while(std::getline(ifs, line_buffer))
    {
      auto semicolon = line_buffer.find(':');
      if(semicolon == string::npos)
        continue;
      string key = line_buffer.substr(0, semicolon);
      auto is_json_junk = [](char c){ return isspace(c) or c == '"' or c == ','; };
      auto is_digit = [](char c){ return isdigit(c); };
      key.erase(std::remove_if(key.begin(), key.end(), is_json_junk), key.end());
      string value_str = line_buffer.substr(semicolon + 1, line_buffer.size());
      value_str.erase(std::remove_if(value_str.begin(), value_str.end(), is_json_junk), value_str.end());
      variant<string, u16> value;
      if(std::all_of(value_str.cbegin(), value_str.cend(), is_digit))
        value = static_cast<u16>(std::stoi(value_str));
      else
        value = value_str;
      m_values[EnumerationDictionary.inverse().at(key)] = value;
      cout << "\tLoaded key (" << key << "), value (" << value_str << ")" << endl;
    }
  }
} // HSA