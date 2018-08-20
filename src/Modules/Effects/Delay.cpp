#include "Delay.hpp"

namespace Synth {

  Delay::Delay()
  : _sample_rate(44100),
    _channel_count(2),
    _decay(.5),
    _feedback(0.35),
    _mix(.65),
    _cursor(0)
  {
    updateBufferCount();
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

  void Delay::setChannelCount(double channel_count)
  {
    _channel_count = _channel_count;
    updateBufferCount();
  }
  double Delay::getChannelCount() const
  { return _channel_count; }

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

  void Delay::process(double samples[])
  {
    for (int i = 0; i < _channel_count; ++i) {
      double delayed = _buffer[i][_cursor[i]];

      _buffer[i][_cursor[i]] = samples[i] + delayed * _feedback;
      _cursor[i] += 1;
      if (_cursor[i] >= _buffer[i].size())
        _cursor[i] = 0;
      samples[i] = samples[i] * (1 - _mix) + delayed * _mix;
    }
  }

  void Delay::updateBufferSize()
  {
    size_t count = _sample_rate * _decay;

    for (int i = 0; i < _channel_count; ++i) {
      _buffer[i].resize(count, 0);
      if (_cursor[i] >= count)
        _cursor[i] = 0;
    }
  }

  void Delay::updateBufferCount()
  {
    _cursor.resize(_channel_count, 0);
    _buffer.resize(_channel_count);
    updateBufferSize();
  }
}