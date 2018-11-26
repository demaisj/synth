#pragma once

namespace midi {
namespace protocol {

enum command_type {
  note_off         = 0x80,
  note_on          = 0x90,
  note_pressure    = 0xA0,
  control_change   = 0xB0,
  program_change   = 0xC0,
  channel_pressure = 0xD0,
  pitch_bend       = 0xE0,
  system           = 0xF0
};

constexpr bool is_command(unsigned char byte) { return (byte & 0x80) == 0x80; }

constexpr unsigned char get_command_type(unsigned char byte) { return byte & 0xF0; }
constexpr unsigned char get_command_channel(unsigned char byte) { return byte & 0x0F; }

constexpr int data_size(unsigned char byte)
{
  switch (get_command_type(byte)) {
    case command_type::note_off:
    case command_type::note_on:
    case command_type::note_pressure:
    case command_type::control_change:
    case command_type::program_change:
    case command_type::pitch_bend:
      return 2;
    case command_type::channel_pressure:
      return 1;
    default:
      return 0;
  }
}

}
}