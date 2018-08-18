#include "Message.hpp"

namespace MIDI {

  MessageChannel::MessageChannel(int channel)
  : _channel(channel)
  {}
  MessageChannel::~MessageChannel()
  {}

  int MessageChannel::getChannel() const
  { return _channel; }


  MessageNote::MessageNote(int channel, int note, int velo)
  : MessageChannel(channel),
    _note(note),
    _velo(velo)
  {}
  MessageNote::~MessageNote()
  {}

  int MessageNote::getNote() const
  { return _note; }
  int MessageNote::getVelo() const
  { return _velo; }


  MessageNoteOn::MessageNoteOn(int channel, int note, int velo)
  : MessageNote(channel, note, velo)
  {}
  MessageNoteOn::~MessageNoteOn()
  {}

  Message MessageNoteOn::getType() const
  { return Message::NoteOn; }

  std::ostream &MessageNoteOn::serialize(std::ostream &stream) const
  {
    return stream << "MessageNoteOn(channel=" << getChannel()
      << ", note=" << getNote()
      << ", velo=" << getVelo()
      << ")";
  }


  MessageNoteOff::MessageNoteOff(int channel, int note, int velo)
  : MessageNote(channel, note, velo)
  {}
  MessageNoteOff::~MessageNoteOff()
  {}

  Message MessageNoteOff::getType() const
  { return Message::NoteOff; }

  std::ostream &MessageNoteOff::serialize(std::ostream &stream) const
  {
    return stream << "MessageNoteOff(channel=" << getChannel()
      << ", note=" << getNote()
      << ", velo=" << getVelo()
      << ")";
  }


  MessagePitchBend::MessagePitchBend(int channel, int value)
  : MessageChannel(channel),
    _value(value)
  {}
  MessagePitchBend::~MessagePitchBend()
  {}

  Message MessagePitchBend::getType() const
  { return Message::PitchBend; }
  int MessagePitchBend::getValue() const
  { return _value; }

  std::ostream &MessagePitchBend::serialize(std::ostream &stream) const
  {
    return stream << "MessagePitchBend(channel=" << getChannel()
      << ", value=" << getValue()
      << ")";
  }


  MessageControlChange::MessageControlChange(int channel, int number, int value)
  : MessageChannel(channel),
    _number(number),
    _value(value)
  {}
  MessageControlChange::~MessageControlChange()
  {}

  Message MessageControlChange::getType() const
  { return Message::ControlChange; }
  int MessageControlChange::getNumber() const
  { return _number; }
  int MessageControlChange::getValue() const
  { return _value; }

  std::ostream &MessageControlChange::serialize(std::ostream &stream) const
  {
    return stream << "MessageControlChange(channel=" << getChannel()
      << ", number=" << getNumber()
      << ", value=" << getValue()
      << ")";
  }


  std::ostream& operator<<(std::ostream &stream, std::unique_ptr<const IMessage> &message)
  {
    return message->serialize(stream);
  }

}