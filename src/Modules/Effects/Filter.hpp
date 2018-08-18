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

    void setCutoff(double cutoff);
    double getCutoff() const;

    void setResonance(double resonance);
    double getResonance() const;

    void setMode(Mode mode);
    Mode getMode() const;

    double process(double sample);

  private:
    double _sample_rate;

    Mode _mode = Mode::LowPass;
    double _cutoff;
    double _resonance;

    double _buf[4] = { 0 };
    double _feedback = 0;

    void updateFeedbackAmount();
  };

}