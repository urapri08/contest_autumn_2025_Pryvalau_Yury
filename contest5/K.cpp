#include <iostream>
const int cZero = 0;
const int cOne = 1;
const int cTwo = 2;
const int cMaxN = 250005;
int global_n;
int a[cMaxN];
int d[cMaxN];
int p[cMaxN];
int ans[cMaxN];
void ReadInput() {
  std::cin >> global_n;
  for (int i = cOne; i <= global_n; i++) {
    std::cin >> a[i];
  }
}
void SolveProblem() {
  int max_len;
  max_len = cZero;
  for (int i = cOne; i <= global_n; i++) {
    int left;
    left = cOne;
    int right;
    right = max_len;
    int pos;
    pos = max_len + cOne;
    int x;
    x = a[i];
    while (left <= right) {
      int mid;
      mid = left + (right - left) / cTwo;
      if (a[d[mid]] < x) {
        pos = mid;
        right = mid - cOne;
      }
      else {
        left = mid + cOne;
      }
    }
    d[pos] = i;
    p[i] = d[pos - cOne];
    if (pos > max_len) {
      max_len = pos;
    }
  }
  std::cout << max_len << "\n";
  int curr;
  curr = d[max_len];
  int k;
  k = cZero;
  while (curr != cZero) {
    ans[k] = curr;
    k++;
    curr = p[curr];
  }
  for (int i = k - cOne; i >= cZero; i--) {
    std::cout << ans[i];
    if (i > cZero) {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}
void Solve() {
  ReadInput();
  SolveProblem();
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solve();
  return cZero;
}