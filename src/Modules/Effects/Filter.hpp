namespace Synth {

  class Filter {
  public:
    enum class Mode : int {
      LowPass,
      HighPass,
      BandPass
    };

    Filter();
    ~Filter();

    void setSampleRate(double sample_rate);
    double getSampleRate() const;

    void setChannelCount(double channel_count);
    double getChannelCount() const;

    void setCutoff(double cutoff);
    double getCutoff() const;

    void setResonance(double resonance);
    double getResonance() const;

    void setMode(Mode mode);
    Mode getMode() const;

    void process(double samples[]);

  private:
    double _sample_rate;
    double _channel_count;

    Mode _mode = Mode::LowPass;
    double _cutoff;
    double _resonance;

    double _buf[4] = { 0 };
    double _feedback = 0;

    void updateFeedbackAmount();
  };

}