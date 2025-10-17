#include <cstdint>
#include <iostream>
#include <vector>

const int cBitsPerPass = 8;
const int cNumPasses = sizeof(uint64_t);
const int cBucketSize = 1 << cBitsPerPass;
const uint64_t cMask = (1ULL << cBitsPerPass) - 1;

void LsdRadixSort(std::vector<uint64_t>& list) {
  if (list.empty()) {
    return;
  }
  long long length = list.size();
  std::vector<uint64_t> temp_list(length);
  std::vector<long long> counts(cBucketSize);

  for (int pass = 0; pass < cNumPasses; ++pass) {
    for (int i = 0; i < cBucketSize; ++i) {
      counts[i] = 0;
    }
    int shift = pass * cBitsPerPass;
    for (long long i = 0; i < length; ++i) {
      uint8_t byte_value = (list[i] >> shift) & cMask;
      counts[byte_value]++;
    }
    for (int i = 1; i < cBucketSize; ++i) {
      counts[i] += counts[i - 1];
    }
    for (long long i = length - 1; i >= 0; --i) {
      uint8_t byte_value = (list[i] >> shift) & cMask;
      temp_list[--counts[byte_value]] = list[i];
    }
    for (long long i = 0; i < length; ++i) {
      list[i] = temp_list[i];
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  long long n;
  if (!(std::cin >> n)) {
    return 0;
  }
  std::vector<uint64_t> vect(n);
  for (long long i = 0; i < n; ++i) {
    if (!(std::cin >> vect[i])) {
      return 0;
    }
  }
  LsdRadixSort(vect);
  for (long long i = 0; i < n; ++i) {
    std::cout << vect[i];
    if (i != n - 1) {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  return 0;
}