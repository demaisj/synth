namespace Synth {

  class Envelope {
  public:
    enum class Stage : int {
      Attack,
      Hold,
      Decay,
      Sustain,
      Release,
      kStageCount,
      Off
    };

    Envelope();
    ~Envelope();

    void setSampleRate(double sample_rate);
    double getSampleRate() const;

    void trigger();
    void release();

    double generate();

    void setParam(Stage stage, double value);

    void reset();

    Stage getStage() const;

  private:
    double _sample_rate;
    Stage _stage;
    double _level;

    double _params[static_cast<int>(Stage::kStageCount)] = {
      0.005,
      .25,
      1,
      .5,
      .5
    };

    unsigned long long int _index;
    unsigned long long int _stage_start;
    unsigned long long int _stage_next;
    double _stage_level;

    void setStage(Stage next);
  };

}