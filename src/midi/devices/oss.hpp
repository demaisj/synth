#pragma once

#include <filesystem>
#include <cstdio>
#include <cerrno>
#include <system_error>

#include "../types.hpp"
#include "../protocol.hpp"
#include "base.hpp"

namespace midi {

class oss_device : public device_base
{
public:
  oss_device(const std::filesystem::path &path)
  : _path(path) {}
  ~oss_device()
  {
    close();
  }

  const std::string string() const
  {
    return "midi::oss_device(path=" + _path.string() + ")";
  }

  const std::string name() const
  {
    return "OSS: " + _path.string();
  }

  void open()
  {
    _file = fopen(_path.c_str(), "r");
    if (_file == nullptr)
      throw std::system_error(errno, std::generic_category());
  }

  void close()
  {
    if (_file != nullptr) {
      fclose(_file);
      _file = nullptr;
    }
  }

  size_t read(unsigned char data[])
  {
    size_t size = fread(&data[0], sizeof(char), 1, _file);
    if (size <= 0 || !protocol::is_command(data[0])) {
      return 0;
    }

    int data_size = protocol::data_size(data[0]);
    if (data_size <= 0) {
      return 1;
    }

    size = fread(&data[1], sizeof(char), data_size, _file);
    return 1 + size;
  }

  static void probe(prober_results &results)
  {
    for (const auto &entry : std::filesystem::directory_iterator("/dev")) {
      if (entry.path().filename().string().find("midi", 0) == 0)
        results.push_back(std::make_unique<oss_device>(entry.path()));
    }
  }

private:
  std::filesystem::path _path;
  FILE *_file = nullptr;

};

}