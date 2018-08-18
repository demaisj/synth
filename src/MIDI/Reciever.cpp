#include "Reciever.hpp"

namespace MIDI {

  Reciever::Reciever(std::istream &in)
  : _in(in)
  {}
  Reciever::~Reciever()
  {}

  void Reciever::processIncomingData()
  {
    char message;

    _in.get(message);
    if (message) {

      if ((message >> 7 & 0x1) == 0) {
        std::cerr << "midi: Erroneous command." << std::endl;
        return;
      }

      int command = message >> 4 & 0x7;
      int param = message & 0xF;

      try {
        _events.push(makeMessage(command, param));
      }
      catch (std::exception &e) {
        std::cerr << "midi: error/Not implemented." << std::endl;
        return;
      }
    }
  }

  std::unique_ptr<const IMessage> Reciever::getMessage()
  {
    if (_events.empty())
      return nullptr;

    std::unique_ptr<const IMessage> value = std::move(_events.front());
    _events.pop();

    return value;
  }

  std::unique_ptr<const IMessage> Reciever::makeMessage(int command, int param0)
  {
    char data[2] = { 0 };
    int param1, param2;

    switch (command) {
    case 0: // NoteOff
      _in.read(data, 2);
      param1 = data[0] & 0x7F; // note
      param2 = data[1] & 0x7F; // velo
      return std::make_unique<MessageNoteOff>(param0, param1, param2);

    case 1: // NoteOn
      _in.read(data, 2);
      param1 = data[0] & 0x7F; // note
      param2 = data[1] & 0x7F; // velo
      return std::make_unique<MessageNoteOn>(param0, param1, param2);

    case 3: // ControlChange
      _in.read(data, 2);
      param1 = data[0] & 0x7F; // number
      param2 = data[1] & 0x7F; // value

      switch (param1) {
      default:
        return std::make_unique<MessageControlChange>(param0, param1, param2);
      }

    case 6:
      _in.read(data, 2);
      param1 = (data[0] & 0x7F) | ((data[1] & 0x7F) << 7); // value
      return std::make_unique<MessagePitchBend>(param0, param1);

    default:
      throw std::runtime_error("Unknown command");
    }
  }

}