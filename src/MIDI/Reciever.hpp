#include <iostream>
#include <memory>
#include <queue>

#include "MIDI/Message.hpp"

namespace MIDI {

  class Reciever {
  public:

    Reciever(std::istream &in);
    ~Reciever();

    void processIncomingData();

    std::unique_ptr<const IMessage> getMessage();

  private:
    std::istream &_in;
    std::queue<std::unique_ptr<const IMessage>> _events;

    std::unique_ptr<const IMessage> makeMessage(int command, int param0);
  };

}