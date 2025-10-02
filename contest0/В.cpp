#include <stdint.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
const int32_t cTen = 10;
int main() {
  int32_t right;
  int32_t left;
  int32_t size_input;
  int32_t size_prom;
  std::cin >> size_input;
  std::cout.precision(cTen);
  std::cout << std::fixed;
  std::vector<long double> input(size_input + 1);
  std::vector<long double> pref(size_input + 1);
  for (int32_t i = 1; i <= size_input; i++) {
    std::cin >> input[i];
  }
  pref[0] = 0;
  for (int32_t i = 1; i <= size_input; i++) {
    pref[i] = pref[i - 1] + log2(input[i]);
  }
  std::cin >> size_prom;
  for (int32_t b = 0; b < size_prom; b++) {
    std::cin >> left >> right;
    std::cout << pow(2, (pref[right + 1] - pref[left]) / (right - left + 1.0))
      << "\n";
  }
  return 0;
