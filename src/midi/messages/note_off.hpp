#pragma once

#include "base.hpp"
#include "../protocol.hpp"

namespace midi {

class note_off_message : public message_base
{
public:
  note_off_message(const unsigned char data[])
  : _channel(protocol::get_command_channel(data[0])),
    _note(data[1]),
    _velo(data[2])
    {}

  const std::string string() const
  {
    return "midi::note_off_message(channel=" + std::to_string(_channel) +
      ",note=" + std::to_string(_note) +
      ",velo=" + std::to_string(_velo) + ")";
  }

  char channel() const { return _channel; }
  char note() const { return _note; }
  char velo() const { return _velo; }

private:
  char _channel;
  char _note;
  char _velo;

};

}