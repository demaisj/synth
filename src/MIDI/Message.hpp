#include <iostream>
#include <memory>

namespace MIDI {

  enum class Message {
    NoteOff,
    NoteOn,
    PolyphonicPressure,
    ControlChange,
    ProgramChange,
    ChannelPressure,
    PitchBend,
    System
  };


  class IMessage {
  public:
    virtual Message getType() const = 0;
    virtual std::ostream &serialize(std::ostream &stream) const = 0;
  };


  class MessageChannel : public IMessage {
  public:
    MessageChannel(int channel);
    ~MessageChannel();

    int getChannel() const;

  private:
    int _channel;
  };


  class MessageNote : public MessageChannel {
  public:
    MessageNote(int channel, int note, int velo);
    ~MessageNote();

    int getNote() const;
    int getVelo() const;

  private:
    int _note;
    int _velo;
  };


  class MessageNoteOn : public MessageNote {
  public:
    MessageNoteOn(int channel, int note, int velo);
    ~MessageNoteOn();

    Message getType() const;

    std::ostream &serialize(std::ostream &stream) const;
  };


  class MessageNoteOff : public MessageNote {
  public:
    MessageNoteOff(int channel, int note, int velo);
    ~MessageNoteOff();

    Message getType() const;

    std::ostream &serialize(std::ostream &stream) const ;
  };


  class MessagePitchBend : public MessageChannel {
  public:
    MessagePitchBend(int channel, int value);
    ~MessagePitchBend();

    Message getType() const;
    int getValue() const;

    std::ostream &serialize(std::ostream &stream) const;

  private:
    int _value;
  };


  class MessageControlChange : public MessageChannel {
  public:
    MessageControlChange(int channel, int number, int value);
    ~MessageControlChange();

    Message getType() const;
    int getNumber() const;
    int getValue() const;

    std::ostream &serialize(std::ostream &stream) const;

  private:
    int _number;
    int _value;
  };


  std::ostream& operator<<(std::ostream &stream, std::unique_ptr<const IMessage> &message);

}