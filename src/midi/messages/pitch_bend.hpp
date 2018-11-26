#pragma once

#include "base.hpp"
#include "../protocol.hpp"

namespace midi {

class pitch_bend_message : public message_base
{
public:
  pitch_bend_message(const unsigned char data[])
  : _channel(protocol::get_command_channel(data[0])),
    _value(data[1] | (data[2] << 7))
    {}

  const std::string string() const
  {
    return "midi::pitch_bend_message(channel=" + std::to_string(_channel) +
      ",value=" + std::to_string(_value) + ")";
  }

  char channel() const { return _channel; }
  short value() const { return _value; }

private:
  char _channel;
  short _value;

};

}