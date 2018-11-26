#pragma once

#include <string>
#include <stdexcept>
#include <queue>
#include <array>
#include <windows.h>

#include "base.hpp"

namespace midi {

void __wmm_device_callback(HMIDIIN handle, UINT message, DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR param2);

class wmm_device : public device_base
{
public:
  wmm_device(UINT device_id, const TCHAR *name)
  : _device_id(device_id), _name(name)
  {}

  virtual const std::string string() const
  {
    return "midi::wmm_device(device_id=" + std::to_string(_device_id) + ", name=" + _name + ")";
  }

  virtual const std::string name() const
  {
    return _name;
  }

  virtual void open()
  {
    MMRESULT result = midiInOpen(&_handle, _device_id, (DWORD_PTR) &input_callback, (DWORD_PTR) this, CALLBACK_FUNCTION);
    if (result != MMSYSERR_NOERROR)
      throw std::runtime_error("midiInOpen=" + std::to_string(result));
    midiInStart(_handle);
  }

  virtual void close()
  {
    midiInClose(_handle);
  }

  virtual size_t read(unsigned char data[])
  {
    if (!_input_queue.empty()) {
      auto input = _input_queue.front();
      _input_queue.pop();

      data[0] = input[0];
      data[1] = input[1];
      data[2] = input[2];

      return 3;
    }
    return 0;
  }

  static void probe(prober_results &results)
  {
    UINT midi_count = midiInGetNumDevs();

    for (UINT i = 0; i < midi_count; i++) {
      MIDIINCAPS data;

      if (midiInGetDevCaps(i, &data, sizeof(MIDIINCAPS)) != MMSYSERR_NOERROR)
        continue;

      results.push_back(std::make_unique<wmm_device>(i, data.szPname));
    }
  }

private:
  UINT _device_id;
  std::string _name;
  HMIDIIN _handle;

  std::queue<std::array<unsigned char, 3>> _input_queue;

  static void CALLBACK input_callback(HMIDIIN handle, UINT message, DWORD_PTR instance, DWORD_PTR param1, DWORD_PTR param2)
  {
    wmm_device *that = (wmm_device *) instance;

    if (message == MIM_DATA) {
      std::array<unsigned char, 3> data;

      data[0] = param1 & 0xFF;
      data[1] = (param1 >> 8) & 0xFF;
      data[2] = (param1 >> 16) & 0xFF;

      that->_input_queue.push(data);
    }
  }

};

}