#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
bool check(int32_t point, int32_t length)
{
  if (point == length)
  {
    return true;
  }
  else {
    return false;
  }
}
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
  int32_t j;
  low = 0;
  high = length;
  while (low <= high) {
    mid = low + (high - low) / 2;
    std::vector<bool> removed(length, false);
    for (int32_t i = 0; i < mid; i++) {
      removed[order[i] - 1] = true;
    }

    j = 0;
    for (int32_t i = 0; i < length && j < (int32_t)target.length(); i++) {
      if (!removed[i] && str[i] == target[j]) {
        j++;
      }
    }
    if (check(j, (int32_t)target.length())) {
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  if (check(j, (int32_t)target.length()))
  {
    std::cout << low << std::endl;
  }
  else {
    std::cout << high << std::endl;
  }
  return 0;
}}