#include <stdint.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
int main() {
  float right;
  float left;
  int32_t size_input;
  int32_t size_prom;
  std::cin >> size_input;
  std::cout.precision(2 * 5);
  std::cout << std::fixed;
  std::vector<long double> input(size_input);
  std::vector<long double> pref(size_input);
  for (int32_t i = 0; i < size_input; i++) {
    std::cin >> input[i];
  }
  pref[0] = log2(input[0]);
  for (int32_t i = 1; i < size_input; i++) {
    pref[i] = pref[i - 1] + log2(input[i]);
  }
  std::cin >> size_prom;
  std::vector<int32_t> prom(size_prom * 2);
  for (int32_t z = 0; z < size_prom * 2; z++) {
    std::cin >> prom[z];
  }
  for (int32_t b = 1; b < size_prom * 2; b += 2) {
    left = prom[b - 1];
    right = prom[b];
    if (left != right && left != 0) {
      std::cout << pow(2, (pref[right] - pref[left - 1]) / (right - left + 1.0))
        << "\n";
    }
    else if (left == right) {
      std::cout << input[right] << "\n";
    }
    else {
      std::cout << pow(2, (pref[right]) / (right + 1.0)) << "\n";
    }
  }
  return 0;
}