#pragma once

#include <string>

#include "base.hpp"
#include "../protocol.hpp"

namespace midi {

class channel_pressure_message : public message_base
{
public:
  channel_pressure_message(const unsigned char data[])
  : _channel(protocol::get_command_channel(data[0])),
    _value(data[1])
    {}

  const std::string string() const
  {
    return "midi::channel_pressure_message(channel=" + std::to_string(_channel) +
      ",value=" + std::to_string(_value) + ")";
  }

  char channel() const { return _channel; }
  char value() const { return _value; }

private:
  char _channel;
  char _value;

};

}