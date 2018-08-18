#include "Modules/Generators/Oscillator.hpp"
#include "Modules/Envelopes/Envelope.hpp"

namespace Synth {

  class Voice {
  public:
    Voice();
    ~Voice();

    void activate(int note, int velo);
    void deactivate();

    bool isActive() const;
    bool isReady() const;

    int getNote() const;

    double process();

    void setPitch(int amount);
  private:
    bool _active;
    bool _ready;
    int _note;
    int _pitch;

    Envelope _env;
    Oscillator _osc[16];
    double _velo;

    void updateOscFreq();
  };

}