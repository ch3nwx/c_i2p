#include "14927.h"
#include <iostream>
#include <string>

int main() {
  VendingMachine vm;
  std::string cmd;

  while (std::cin >> cmd) {
    if (cmd == "store") {
      int price;
      std::cin >> price;
      vm.store(price);
    } else if (cmd == "sell") {
      vm.sell();
    }
  }

  vm.printResult();
  return 0;
}
