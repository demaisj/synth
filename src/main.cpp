#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "MIDI/Reciever.hpp"

#include "Modules/Core/PulseOutput.hpp"
#include "Modules/Core/VoiceManager.hpp"

#include "Modules/Effects/Filter.hpp"
#include "Modules/Effects/Delay.hpp"

void audio_worker(MIDI::Reciever &midi) {
  Synth::PulseOutput output;
  Synth::VoiceManager manager;
  Synth::Filter filter;
  Synth::Delay delay;

  filter.setCutoff(0.45);
  filter.setResonance(0);
  delay.setDecay(.5);
  delay.setFeedback(.25);
  delay.setMix(.25);

  while (true) {

    bool pass;
    do {
      auto msg = midi.getMessage();
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

int main()
{
  srand(time(nullptr));

  MIDI::Reciever midi(std::cin);
  std::thread audio(audio_worker, std::ref(midi));

  while (!std::cin.eof()) {
    midi.processIncomingData();
  }

  audio.join();
  return 0;
}