#include <cmath>

#include "Util.hpp"

#include "Oscillator.hpp"

namespace Synth {

  static const double M_2PI = 2 * M_PI;

  Oscillator::Oscillator()
  : _waveform(Waveform::Saw),
    _frequency(440),
    _sample_rate(44100),
    _channel_count(2)
  {
    updatePhaseIncrement();
    updatePhaseBuffer();
    reset();
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

  void Oscillator::setChannelCount(double channel_count)
  {
    _channel_count = _channel_count;
    updatePhaseBuffer();
  }
  double Oscillator::getChannelCount() const
  { return _channel_count; }

  void Oscillator::process(double samples[])
  {
    for (int i = 0; i < _channel_count; ++i) {
      switch (_waveform) {
      case Waveform::Sine: // sin(x)
        samples[i] = sin(_phase[i]);
        break;

      case Waveform::Saw: // 1-(2x)/(2pi)
        samples[i] = 1.0 - (2 * _phase[i] / M_2PI);
        break;

      case Waveform::Triangle: // abs(1-abs(((2x)-pi)/(2pi)))*2-1
        samples[i] = Util::abs(1 - Util::abs((2 * _phase[i] - M_PI) / M_2PI)) * 2 - 1;
        break;

      case Waveform::Square: // 1+2*floor(sin(x))
        if (_phase[i] <= M_PI)
          samples[i] = 1.0;
        else
          samples[i] = -1.0;
        break;
      }
      _phase[i] += _phase_increment;
      if (_phase[i] > M_2PI)
        _phase[i] -= M_2PI;
    }
  }

  void Oscillator::reset()
  {
    for (int i = 0; i < _channel_count; ++i) {
      _phase[i] = fmod(rand(), M_2PI);
    }
  }

  void Oscillator::updatePhaseIncrement()
  {
    _phase_increment = _frequency * M_2PI / _sample_rate;
  }

  void Oscillator::updatePhaseBuffer()
  {
    _phase.resize(_channel_count, 0);
  }

}