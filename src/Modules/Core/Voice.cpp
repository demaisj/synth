#include <cmath>

#include "Util.hpp"
#include "MIDI/Tuner.hpp"

#include "Voice.hpp"

namespace Synth {

  Voice::Voice()
  : _active(false),
    _ready(false)
  {
    //_osc.setWaveform(_osc.Waveform::Saw);
    for (int i = 0; i < 16; ++i) {
      _osc[i].setWaveform(_osc[i].Waveform::Saw);
    }
    _env.setParam(_env.Stage::Attack, 3);
    _env.setParam(_env.Stage::Hold, 0);
    _env.setParam(_env.Stage::Decay, 3);
    _env.setParam(_env.Stage::Sustain, .5);
    _env.setParam(_env.Stage::Release, 3);
  }
  Voice::~Voice()
  {}

  void Voice::activate(int note, int velo)
  {
    _env.reset();
    _env.trigger();
    //_osc.reset();
    for (int i = 0; i < 16; ++i) {
      _osc[i].reset();
    }
    _note = note;
    updateOscFreq();
    _velo = velo / 127.0;
    _active = true;
    _ready = true;
  }

  void Voice::deactivate()
  {
    _env.release();
    _ready = false;
  }

  bool Voice::isActive() const
  { return _active; }
  bool Voice::isReady() const
  { return _ready; }

  int Voice::getNote() const
  { return _note; }

  double Voice::process()
  {
    //double output = _osc.generate();
    double output = 0;
    for (int i = 0; i < 16; ++i) {
      double blend = 0.8;
      if (round(i / 8) == 0)
        blend = 1;
      output += _osc[i].generate() * (blend / 16);
    }

    output *= _velo;
    output *= _env.generate();

    if (_env.getStage() == _env.Stage::Off)
      _active = false;

    return output;
  }

  void Voice::setPitch(int amount)
  {
    _pitch = amount;
    if (_active)
      updateOscFreq();
  }

  void Voice::updateOscFreq()
  {
    //_osc.setFrequency(tuner.getFreq(_note + _pitch));
    for (int i = 0; i < 16; ++i) {
      _osc[i].setFrequency(Util::singleton<MIDI::Tuner>().getFreq(_note + _pitch) + (i / 8 + 1) * .10);
    }
  }

}