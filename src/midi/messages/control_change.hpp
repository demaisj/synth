#pragma once

#include "base.hpp"
#include "../protocol.hpp"

namespace midi {

class control_change_message : public message_base
{
public:
  control_change_message(const unsigned char data[])
  : _channel(protocol::get_command_channel(data[0])),
    _control(data[1]),
    _value(data[2])
    {}

  const std::string string() const
  {
    return "midi::control_change_message(channel=" + std::to_string(_channel) +
      ",control=" + std::to_string(_control) +
      ",value=" + std::to_string(_value) + ")";
  }

  char channel() const { return _channel; }
  char control() const { return _control; }
  char value() const { return _value; }

private:
  char _channel;
  char _control;
  char _value;

};

}