#include "Delay.hpp"

namespace Synth {

  Delay::Delay()
  : _sample_rate(44100),
    _decay(.5),
    _feedback(0.35),
    _mix(.65),
    _cursor(0)
  {
    updateBufferSize();
  }
  Delay::~Delay()
  {}

  void Delay::setSampleRate(double sample_rate)
  {
    _sample_rate = sample_rate;
    updateBufferSize();
  }
  double Delay::getSampleRate() const
  { return _sample_rate; }

  void Delay::setDecay(double decay)
  {
    _decay = decay;
    updateBufferSize();
  }
  double Delay::getDecay() const
  { return _decay; }

  void Delay::setFeedback(double feedback)
  { _feedback = feedback; }
  double Delay::getFeedback() const
  { return _feedback; }

  void Delay::setMix(double mix)
  { _mix = mix; }
  double Delay::getMix() const
  { return _mix; }

  double Delay::process(double sample)
  {
    double delayed = _buffer[_cursor];

    _buffer[_cursor] = sample + delayed * _feedback;
    _cursor += 1;
    if (_cursor >= _buffer.size())
      _cursor = 0;
    return sample * (1 - _mix) + delayed * _mix;
  }

  void Delay::updateBufferSize()
  {
    size_t count = _sample_rate * _decay;

    _buffer.resize(count, 0);
    if (_cursor >= count)
      _cursor = 0;
  }
}