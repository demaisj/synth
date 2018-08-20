#include "Filter.hpp"

namespace Synth {

  Filter::Filter()
  : _sample_rate(44100),
    _channel_count(2),
    _cutoff(.01),
    _resonance(.5)
  {
      updateFeedbackAmount();
  }
  Filter::~Filter()
  {}

  void Filter::setSampleRate(double sample_rate)
  { _sample_rate = sample_rate; }
  double Filter::getSampleRate() const
  { return _sample_rate; }

  void Filter::setChannelCount(double channel_count)
  { _channel_count = _channel_count; }
  double Filter::getChannelCount() const
  { return _channel_count; }

  void Filter::setCutoff(double cutoff)
  {
    _cutoff = cutoff;
    updateFeedbackAmount();
  }
  double Filter::getCutoff() const
  { return _cutoff; }

  void Filter::setResonance(double resonance)
  {
    _resonance = resonance;
    updateFeedbackAmount();
  }
  double Filter::getResonance() const
  { return _resonance; }

  void Filter::setMode(Mode mode)
  { _mode = mode; }
  Filter::Mode Filter::getMode() const
  { return _mode; }

  void Filter::process(double samples[])
  {
    for (int i = 0; i < _channel_count; ++i) {
      // http://www.musicdsp.org/showone.php?id=29
      // infinite impulse response filter
      // https://en.wikipedia.org/wiki/Low-pass_filter#Simple_infinite_impulse_response_filter
      //_buf[0] += _cutoff * (sample - buf[0]);
      _buf[0] += _cutoff * (samples[i] - _buf[0] + _feedback * (_buf[0] - _buf[1]));
      _buf[1] += _cutoff * (_buf[0] - _buf[1]);
      // 12db above, 24db below
      _buf[2] += _cutoff * (_buf[1] - _buf[2]);
      _buf[3] += _cutoff * (_buf[2] - _buf[3]);

      switch (_mode) {
      case Mode::LowPass:
          samples[i] = _buf[1];
          break;
      case Mode::HighPass:
          samples[i] = samples[i] - _buf[0];
          break;
      case Mode::BandPass:
          samples[i] = _buf[0] - _buf[1];
          break;
      default:
          samples[i] = 0.0;
          break;
      }
    }
  }

  void Filter::updateFeedbackAmount()
  {
    _feedback = _resonance + _resonance / (1.0 - _cutoff);
  }
}