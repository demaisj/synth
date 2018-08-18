#include <stdexcept>
#include <algorithm>
#include <climits>
#include <pulse/error.h>

#include "PulseOutput.hpp"

namespace Synth {

  PulseOutput::PulseOutput(uint32_t sample_rate, uint32_t bit_depth, uint32_t channels)
  : _sample_rate(sample_rate),
    _bit_depth(bit_depth),
    _channels(channels)
  {
    int error;

    pa_sample_spec spec;
    switch (_bit_depth) {
    case 8:
      spec.format = PA_SAMPLE_U8;
      break;
    case 16:
      spec.format = PA_SAMPLE_S16NE;
      break;
    default:
      spec.format = PA_SAMPLE_INVALID;
    }
    spec.channels = _channels;
    spec.rate = _sample_rate;

    _pulse = pa_simple_new(
      nullptr,
      "Synth",
      PA_STREAM_PLAYBACK,
      nullptr,
      "playback",
      &spec,
      nullptr,
      nullptr,
      &error
    );

    if (!_pulse)
      throw std::runtime_error(pa_strerror(error));
  }
  PulseOutput::~PulseOutput()
  {
    pa_simple_drain(_pulse, nullptr);
    pa_simple_free(_pulse);
  }

  void PulseOutput::feed(const double samples[])
  {
    switch (_bit_depth) {
    case 8:
      feed8(samples);
      break;
    case 16:
      feed16(samples);
      break;
    }
  }

  void PulseOutput::feed8(const double samples[])
  {
    int error;
    unsigned char out[_channels];

    for (unsigned int i = 0; i < _channels; ++i) {
      double modified = (samples[i] + 1) * .5 * UCHAR_MAX;
      out[i] = std::min(modified, static_cast<double>(UCHAR_MAX));
    }

    if (pa_simple_write(_pulse, out, sizeof(out), &error) < 0)
      throw std::runtime_error(pa_strerror(error));
  }

  void PulseOutput::feed16(const double samples[])
  {
    int error;
    int16_t out[_channels];

    for (unsigned int i = 0; i < _channels; ++i) {
      double modified = samples[i] * INT16_MAX;
      out[i] = std::min(std::max(modified, static_cast<double>(INT16_MIN)), static_cast<double>(INT16_MAX));
    }

    //std::cout << out[0] << "," << out[1] << '\r';

    if (pa_simple_write(_pulse, out, sizeof(out), &error) < 0)
      throw std::runtime_error(pa_strerror(error));
  }
}