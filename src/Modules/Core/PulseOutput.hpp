#include <pulse/simple.h>

namespace Synth {

  class PulseOutput {
  public:
    PulseOutput(uint32_t sample_rate=44100, uint32_t bit_depth=16, uint32_t channels=2);
    ~PulseOutput();

    void feed(const double samples[]);

  private:
    pa_simple *_pulse;
    uint32_t _sample_rate;
    uint32_t _bit_depth;
    uint32_t _channels;

    void feed8(const double samples[]);
    void feed16(const double samples[]);
  };

}