#include <vector>

namespace Synth {

  class Delay {
  public:
    Delay();
    ~Delay();

    void setSampleRate(double sample_rate);
    double getSampleRate() const;

    void setDecay(double decay);
    double getDecay() const;

    void setFeedback(double feedback);
    double getFeedback() const;

    void setMix(double mix);
    double getMix() const;

    double process(double sample);

  private:
    double _sample_rate;
    double _decay;
    double _feedback;
    double _mix;

    double _cursor;
    std::vector<double> _buffer;

    void updateBufferSize();
  };

}