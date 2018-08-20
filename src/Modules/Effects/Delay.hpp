#include <vector>

namespace Synth {

  class Delay {
  public:
    Delay();
    ~Delay();

    void setSampleRate(double sample_rate);
    double getSampleRate() const;

    void setChannelCount(double channel_count);
    double getChannelCount() const;

    void setDecay(double decay);
    double getDecay() const;

    void setFeedback(double feedback);
    double getFeedback() const;

    void setMix(double mix);
    double getMix() const;

    void process(double samples[]);

  private:
    double _sample_rate;
    double _channel_count;
    double _decay;
    double _feedback;
    double _mix;

    std::vector<double> _cursor;
    std::vector<std::vector<double>> _buffer;

    void updateBufferSize();
    void updateBufferCount();
  };

}