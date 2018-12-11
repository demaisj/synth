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

    oss_device::probe(results);
    alsa_device::probe(results);

    #elif defined(_WIN32) || defined(_WIN64)

    wmm_device::probe(results);

    #endif

    return results;
  }

};

}