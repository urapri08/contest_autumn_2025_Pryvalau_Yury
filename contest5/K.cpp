#include <iostream>
#include <vector>
const int cZero = 0;
const int cOne = 1;
const int cTwo = 2;
const int cMaxN = 250'005;

void ReadInput(int& n, std::vector<int>& a) {
  std::cin >> n;
  a.resize(n + cOne);
  for (int i = cOne; i <= n; i++) {
    std::cin >> a[i];
  }
}

void SolveProblem(int n, const std::vector<int>& a) {
  int max_len = cZero;
  std::vector<int> d(n + cOne, cZero);
  std::vector<int> p(n + cOne, cZero);
  for (int i = cOne; i <= n; i++) {
    int left = cOne;
    int right = max_len;
    int pos = max_len + cOne;
    int x = a[i];
    while (left <= right) {
      int mid = left + (right - left) / cTwo;
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
  std::cout << max_len << '\n';
  int curr = d[max_len];
  int k = cZero;
  std::vector<int> ans(n + cOne, cZero);
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
  std::cout << '\n';
}

void Solve() {
  int n = cZero;
  std::vector<int> a;
  ReadInput(n, a);
  SolveProblem(n, a);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solve();
  return cZero;
}