#include "Modules/Core/Voice.hpp"

namespace Synth {

  class VoiceManager {
  public:
    VoiceManager();
    ~VoiceManager();

    void noteOn(int note, int velo);
    void noteOff(int note);

    void pitchBend(int amount);

    double process();

  private:
    bool _legato = false;

    static const int _voice_count = 64;
    Voice _voices[_voice_count];
  };

}