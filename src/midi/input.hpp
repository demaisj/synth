#pragma once

#include "device.hpp"
#include "message.hpp"

namespace midi {

class input
{
public:
  input(device_base::pointer &device)
  : _device(device)
  {
    _device->open();
  }

  ~input()
  {
    _device->close();
  }

  void read()
  {
    unsigned char data[12];
    size_t size = _device->read(data);

    if (size > 0) {
      printf("READ %luB: ", size);
      for (size_t i = 0; i < size; ++i) {
        printf("%02X", data[i] & 0xFF);
      }
      auto msg = message_base::build(data);
      if (msg != nullptr)
        std::cout << " = " << *msg << std::endl;
      else
        std::cout << " = nullptr" << std::endl;
    }
  }

private:
  device_base::pointer &_device;
};

}