#include <vector>

namespace Synth {

  class Oscillator {
  public:
    enum class Waveform {
      Sine,
      Saw,
      Triangle,
      Square
    };

    Oscillator();
    ~Oscillator();

    void setWaveform(Waveform waveform);
    Waveform getWaveform() const;

    void setFrequency(double frequency);
    double getFrequency() const;

    void setSampleRate(double sample_rate);
    double getSampleRate() const;

    void setChannelCount(double channel_count);
    double getChannelCount() const;

    void process(double samples[]);

    void reset();

  private:
    Waveform _waveform;
    double _frequency;
    double _sample_rate;
    double _channel_count;

    std::vector<double> _phase;
    double _phase_increment;

    void updatePhaseIncrement();
    void updatePhaseBuffer();
  };

}