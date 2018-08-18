#include <cmath>

#include "Util.hpp"

#include "Oscillator.hpp"

namespace Synth {

  static const double M_2PI = 2 * M_PI;

  Oscillator::Oscillator()
  : _waveform(Waveform::Saw),
    _frequency(440),
    _sample_rate(44100)
  {
    reset();
    updatePhaseIncrement();
  }
  Oscillator::~Oscillator()
  {}

  void Oscillator::setWaveform(Waveform waveform)
  { _waveform = waveform; }
  Oscillator::Waveform Oscillator::getWaveform() const
  { return _waveform; }

  void Oscillator::setFrequency(double frequency)
  {
    _frequency = frequency;
    updatePhaseIncrement();
  }
  double Oscillator::getFrequency() const
  { return _frequency; }

  void Oscillator::setSampleRate(double sample_rate)
  {
    _sample_rate = sample_rate;
    updatePhaseIncrement();
  }
  double Oscillator::getSampleRate() const
  { return _sample_rate; }

  double Oscillator::generate()
  {
    double sample = 0;

    switch (_waveform) {
    case Waveform::Sine: // sin(x)
      sample = sin(_phase);
      break;

    case Waveform::Saw: // 1-(2x)/(2pi)
      sample = 1.0 - (2 * _phase / M_2PI);
      break;

    case Waveform::Triangle: // abs(1-abs(((2x)-pi)/(2pi)))*2-1
      sample = Util::abs(1 - Util::abs((2 * _phase - M_PI) / M_2PI)) * 2 - 1;
      break;

    case Waveform::Square: // 1+2*floor(sin(x))
      if (_phase <= M_PI)
        sample = 1.0;
      else
        sample = -1.0;
      break;
    }
    _phase += _phase_increment;
    if (_phase > M_2PI)
      _phase -= M_2PI;
    return sample;
  }

  void Oscillator::reset()
  {
    _phase = fmod(rand(), M_2PI);
  }

  void Oscillator::updatePhaseIncrement()
  {
    _phase_increment = _frequency * M_2PI / _sample_rate;
  }

}