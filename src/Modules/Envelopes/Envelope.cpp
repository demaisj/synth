#include "Envelope.hpp"

namespace Synth {

  Envelope::Envelope()
  : _sample_rate(44100)
  {
    reset();
  }
  Envelope::~Envelope()
  {}

  void Envelope::setSampleRate(double sample_rate)
  { _sample_rate = sample_rate; }
  double Envelope::getSampleRate() const
  { return _sample_rate; }

  void Envelope::trigger()
  { setStage(Envelope::Stage::Attack); }
  void Envelope::release()
  { setStage(Envelope::Stage::Release); }

  double Envelope::generate()
  {
    double next_level = 0;
    Stage next_stage;

    if (_stage == Envelope::Stage::Off)
      return 0;

    switch (_stage) {
    case Envelope::Stage::Attack:
      next_level = static_cast<double>(_index - _stage_start) / static_cast<double>(_stage_next - _stage_start);
      next_stage = Envelope::Stage::Hold;
      break;

    case Envelope::Stage::Hold:
      next_level = 1;
      next_stage = Envelope::Stage::Decay;
      break;

    case Envelope::Stage::Decay:
      next_level = 1 - (static_cast<double>(_index - _stage_start) / static_cast<double>(_stage_next - _stage_start) * (1 - _params[static_cast<int>(Envelope::Stage::Sustain)]));
      next_stage = Envelope::Stage::Sustain;
      break;

    case Envelope::Stage::Sustain:
      next_level = _params[static_cast<int>(Envelope::Stage::Sustain)];
      break;

    case Envelope::Stage::Release:
      next_level = _stage_level - (static_cast<double>(_index - _stage_start) / static_cast<double>(_stage_next - _stage_start) * _stage_level);
      next_stage = Envelope::Stage::Off;
      break;
    }

    //std::cout << next_level << std::endl;

    _level = next_level;

    if (_index > _stage_next && _stage != Envelope::Stage::Sustain)
      setStage(next_stage);

    _index++;

    return _level;
  }

  void Envelope::setParam(Stage stage, double value)
  {
    if (stage == Envelope::Stage::Off)
      return;

    _params[static_cast<int>(stage)] = value;
  }

  void Envelope::reset()
  {
    _stage = Envelope::Stage::Off;
  }

  Envelope::Stage Envelope::getStage() const
  { return _stage; }


  void Envelope::setStage(Stage next)
  {
    //std::cout << static_cast<int>(next) << std::endl;

    if (next == Envelope::Stage::Attack) {
      _index = 0;
      _level = 0;
      _stage_start = 0;
      _stage_level = 0;
    }
    else {
      _stage_start = _index;
      _stage_level = _level;
    }

    _stage = next;
    //std::cout << "stage change! " << static_cast<int>(_stage) << std::endl;

    //std::cout << "index: " << _index << std::endl;
    //std::cout << "start: " << _stage_start << std::endl;
    //std::cout << "level: " << _level << std::endl;

    if (_stage == Envelope::Stage::Sustain || _stage == Envelope::Stage::Off)
      return;

    _stage_next = _stage_start + _params[static_cast<int>(_stage)] * _sample_rate;

    //std::cout << "next: " << _stage_next << std::endl;
  }

}