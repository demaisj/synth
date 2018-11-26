#pragma once

#include <memory>
#include <iostream>
#include <string>

namespace midi {

class device_base
{
public:
  typedef std::unique_ptr<device_base> pointer;

  virtual const std::string string() const = 0;
  virtual const std::string name() const = 0;

  virtual void open() = 0;
  virtual void close() = 0;

  virtual size_t read(unsigned char data[]) = 0;

};

std::ostream &operator<<(std::ostream &stream, const device_base &device)
{
  return stream << device.string();
}

}