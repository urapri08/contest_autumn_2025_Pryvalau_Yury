#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
int main() {
  std::string str;
  std::string target;
  std::cin >> str >> target;
  int32_t length;
  length = str.length();
  std::vector<int32_t> order(length);
  for (int32_t i = 0; i < length; i++) {
    std::cin >> order[i];
  }
  int32_t low;
  int32_t high;
  int32_t mid;
  int32_t ans;
  low = 0;
  high = length;
  ans = 0;
  while (low <= high) {
    mid = low + (high - low) / 2;
    std::vector<bool> removed(length, false);
    for (int32_t i = 0; i < mid; i++) {
      removed[order[i] - 1] = true;
    }
    int32_t j;
    j = 0;
    for (int32_t i = 0; i < length && j < (int32_t)target.length(); i++) {
      if (!removed[i] && str[i] == target[j]) {
        j++;
      }
    }
    if (j == (int32_t)target.length()) {
      ans = mid;
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  std::cout << ans << std::endl;
  return 0;
}