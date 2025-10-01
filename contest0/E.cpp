#include <stdint.h>
#include <iostream>
#include <vector>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int32_t num;
  std::cin >> num;
  std::vector<int64_t> lista(num);
  std::vector<int64_t> listb(num);
  for (int32_t i = 0; i < num; i++) {
    std::cin >> lista[i];
  }
  for (int32_t i = 0; i < num; i++) {
    std::cin >> listb[i];
  }
  int32_t query;
  std::cin >> query;
  while (query > 0) {
    query--;
    int64_t xval;
    std::cin >> xval;
    int32_t low = 0;
    int32_t high = num - 1;
    int32_t point = num;
    while (low <= high) {
      int32_t mid = low + (high - low) / 2;
      if (lista[mid] + xval >= listb[mid]) {
        point = mid;
        high = mid - 1;
      }
      else {
        low = mid + 1;
      }
    }
    int32_t result;
    if (point == 0) {
      result = 0;
    }
    else if (point == num) {
      result = num - 1;
    }
    else {
      int64_t v1 = lista[point - 1] + xval;
      if (v1 < listb[point - 1]) {
        v1 = listb[point - 1];
      }
      int64_t v2 = lista[point] + xval;
      if (v2 < listb[point]) {
        v2 = listb[point];
      }
      if (v1 <= v2) {
        result = point - 1;
      }
      else {
        result = point;
      }
    }
    std::cout << result + 1 << '\n';
  }
  return 0;
}