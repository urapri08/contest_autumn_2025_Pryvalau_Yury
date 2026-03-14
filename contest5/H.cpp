#include <iostream>
const int cZero = 0;
const int cOne = 1;
const int cTwo = 2;
const int cMaxN = 2005;
unsigned long long global_dp[cMaxN];
void Solve() {
  int n;
  std::cin >> n;
  unsigned long long total_ways;
  total_ways = cZero;
  for (int x = cOne; x <= n; x++) {
    int target;
    target = n - x;
    if (target == cZero) {
      total_ways = total_ways + cOne;
    }
    if (target > cZero) {
      for (int i = cZero; i <= target; i++) {
        global_dp[i] = cZero;
      }
      global_dp[cZero] = cOne;
      int max_val;
      max_val = x * cTwo - cOne;
      for (int v = x + cOne; v <= max_val; v++) {
        for (int j = target; j >= v; j--) {
          unsigned long long ways;
          ways = global_dp[j - v];
          global_dp[j] = global_dp[j] + ways;
        }
      }
      unsigned long long add_ways;
      add_ways = global_dp[target];
      total_ways = total_ways + add_ways;
    }
  }
  std::cout << total_ways << "\n";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solve();
  return cZero;
}
