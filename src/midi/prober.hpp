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


    #if defined(__linux__)

    fs_device::probe(results);
    //alsa_device::probe(results);

    #endif

    return results;
  }

};

}