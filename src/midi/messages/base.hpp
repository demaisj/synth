#pragma once

#include <memory>
#include <iostream>

#include "../protocol.hpp"

namespace midi {

class message_base
{
public:
  typedef std::unique_ptr<message_base> pointer;

  static message_base::pointer build(const unsigned char data[]);

  virtual const std::string string() const = 0;
};

std::ostream &operator<<(std::ostream &stream, const message_base &message)
{
  return stream << message.string();
}

}