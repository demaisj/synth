#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "Modules/Core/PulseOutput.hpp"
#include "Modules/Core/VoiceManager.hpp"

#include "Modules/Effects/Filter.hpp"
#include "Modules/Effects/Delay.hpp"

#include "Synth.hpp"

namespace Synth {

  Synth::Synth()
  : _running(true),
    _midi(std::cin),
    _audio_worker(&Synth::audioWorker, this)
  {
    srand(time(nullptr));
  }

  Synth::~Synth()
  {
    _running = false;
    _audio_worker.join();
  }

  void Synth::audioWorker()
  {
    PulseOutput output;
    VoiceManager manager;
    Filter filter;
    Delay delay;

    filter.setCutoff(0.45);
    filter.setResonance(0);
    delay.setDecay(.5);
    delay.setFeedback(.25);
    delay.setMix(.25);

    while (_running) {

      bool pass;
      do {
        auto msg = _midi.getMessage();
        pass = false;

        if (msg) {
          pass = true;
          std::cerr << msg << std::endl;

          if (msg->getType() == MIDI::Message::NoteOn) {
            auto note = dynamic_cast<const MIDI::MessageNote *>(msg.get());
            manager.noteOn(note->getNote(), note->getVelo());
          }
          else if (msg->getType() == MIDI::Message::NoteOff) {
            auto note = dynamic_cast<const MIDI::MessageNote *>(msg.get());
            manager.noteOff(note->getNote());
          }
          else if (msg->getType() == MIDI::Message::PitchBend) {
            auto pitch = dynamic_cast<const MIDI::MessagePitchBend *>(msg.get());
            manager.pitchBend(pitch->getValue());
          }
          else if (msg->getType() == MIDI::Message::ControlChange) {
            auto control = dynamic_cast<const MIDI::MessageControlChange *>(msg.get());
            if (control->getNumber() == 1) {
              double cutoff = (-log(-(control->getValue() / 127.0)+1)) / 6;
              if (cutoff >= 1)
                cutoff = 0.999999;
              filter.setCutoff(cutoff);
            }
          }
        }
      } while (pass);

      double sample = manager.process();
      sample = filter.process(sample);
      sample = delay.process(sample);
      double frame[2] = { sample, sample };
      output.feed(frame);
    }
  }

  void Synth::run()
  {
    while (!std::cin.eof()) {
      _midi.processIncomingData();
    }
  }

}