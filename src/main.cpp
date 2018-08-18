#include <iostream>
#include <csignal>
#include <cstdlib>

#include "Synth.hpp"

static Synth::Synth instance;

void handler(int signo)
{
  exit(0);
}

int main()
{
  if (signal(SIGINT, handler) == SIG_ERR
    || signal(SIGTERM, handler) == SIG_ERR) {
    std::cerr << "Failed to setup signal." << std::endl;
    return 1;
  }

  instance.run();

  return 0;
}