#include <cstdint>
#include <iostream>
#include <vector>

const int32_t cBitsPerPass = 8;
const int32_t cNumPasses = sizeof(uint64_t);
const int32_t cBucketSize = 1 << cBitsPerPass;
const int64_t cMask = (1ULL << cBitsPerPass) - 1;

void LsdRadixSort(std::vector<int64_t>& list) {
  if (list.empty()) {
    return;
  }
  int64_t length = list.size();
  std::vector<int64_t> temp_list(length);
  std::vector<int64_t> counts(cBucketSize);

  for (int32_t pass = 0; pass < cNumPasses; ++pass) {
    for (int32_t i = 0; i < cBucketSize; ++i) {
      counts[i] = 0;
    }
    int32_t shift = pass * cBitsPerPass;
    for (int64_t i = 0; i < length; ++i) {
      int8_t byte_value = (list[i] >> shift) & cMask;
      counts[byte_value]++;
    }
    for (int32_t i = 1; i < cBucketSize; ++i) {
      counts[i] += counts[i - 1];
    }
    for (int64_t i = length - 1; i >= 0; --i) {
      int8_t byte_value = (list[i] >> shift) & cMask;
      temp_list[--counts[byte_value]] = list[i];
    }
    for (int64_t i = 0; i < length; ++i) {
      list[i] = temp_list[i];
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  int64_t n;
  if (!(std::cin >> n)) {
    return 0;
  }
  std::vector<int64_t> vect(n);
  for (int64_t i = 0; i < n; ++i) {
    if (!(std::cin >> vect[i])) {
      return 0;
    }
  }
  LsdRadixSort(vect);
  for (int64_t i = 0; i < n; ++i) {
    std::cout << vect[i];
    if (i != n - 1) {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  return 0;
}