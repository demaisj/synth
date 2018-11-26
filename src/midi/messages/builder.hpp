#pragma once

#include "../message.hpp"

namespace midi {

message_base::pointer message_base::build(const unsigned char data[])
{
  switch (protocol::get_command_type(data[0])) {
    case protocol::command_type::note_off: return std::make_unique<note_off_message>(data);
    case protocol::command_type::note_on: return std::make_unique<note_on_message>(data);
    //case protocol::command_type::note_pressure: return std::make_unique<note_pressure_message>(data);
    case protocol::command_type::control_change: return std::make_unique<control_change_message>(data);
    //case protocol::command_type::program_change: return std::make_unique<program_change_message>(data);
    case protocol::command_type::channel_pressure: return std::make_unique<channel_pressure_message>(data);
    case protocol::command_type::pitch_bend: return std::make_unique<pitch_bend_message>(data);
    //case protocol::command_type::system: return std::make_unique<system_message>(data);
  }
  return nullptr;
}

}