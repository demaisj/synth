#include <iostream>

#include "midi/prober.hpp"
#include "midi/input.hpp"

int main()
{
  midi::prober prober;

  std::cout << "Probing midi devices..." << std::endl;
  auto results = prober.probe();

  if (results.size() == 0) {
    std::cout << "No devices found." << std::endl;
    return 1;
  }
  std::cout << "Select a device:" << std::endl;
  unsigned int i = 1;
  for (auto &device : results) {
    std::cout << i++ << ": " << device->name() << std::endl;
  }

  unsigned int index = 1;
  if (results.size() > 1) {
    index = 0;
    do {
      std::cin >> index;
    }
    while (index == 0 || index > results.size());
  }

  midi::input input(results[index - 1]);

  while (1) {
    input.read();
  }

  return 0;
}