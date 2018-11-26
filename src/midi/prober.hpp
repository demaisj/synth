#pragma once

#include "types.hpp"
#include "device.hpp"

namespace midi {

class prober
{
public:

  prober_results probe()
  {
    prober_results results;

    fs_device::probe(results);
    //alsa_device::probe(results);

    return results;
  }

};

}