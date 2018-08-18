#include <cmath>

#include "VoiceManager.hpp"

namespace Synth {

  VoiceManager::VoiceManager()
  {}
  VoiceManager::~VoiceManager()
  {}

  void VoiceManager::noteOn(int note, int velo)
  {
    for (int i = 0; i < _voice_count; ++i) {
      if (!_voices[i].isActive()) {
        _voices[i].activate(note, velo);
        break;
      }
    }
  }

  void VoiceManager::noteOff(int note)
  {
    for (int i = 0; i < _voice_count; ++i) {
      if (_voices[i].isActive() && _voices[i].isReady()
        && _voices[i].getNote() == note) {

        _voices[i].deactivate();
        break;
      }
    }
  }

  void VoiceManager::pitchBend(int amount)
  {
    int pitch = round(((amount / 8192.0) - 1.0) * 12.0);

    for (int i = 0; i < _voice_count; ++i) {
      _voices[i].setPitch(pitch);
    }
  }

  double VoiceManager::process()
  {
    double output = 0;

    for (int i = 0; i < _voice_count; ++i) {
      if (_voices[i].isActive())
        output += _voices[i].process();
    }

    return output;
  }

}