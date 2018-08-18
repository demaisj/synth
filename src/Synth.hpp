#include <thread>

#include "MIDI/Reciever.hpp"

namespace Synth {

  class Synth {
  public:
    Synth();
    ~Synth();

    void run();

  private:
    bool _running;
    MIDI::Reciever _midi;
    std::thread _audio_worker;

    void audioWorker();
  };

}