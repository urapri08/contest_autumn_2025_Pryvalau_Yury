#include <cstdint>
#include <iostream>
#include <vector>
void Solve() {
  int n = 0;
  std::cin >> n;
  uint64_t total_ways = 0;
  std::vector<uint64_t> dp(n + 1, 0);
  for (int x = 1; x <= n; x++) {
    int target = n - x;
    if (target == 0) {
      total_ways++;
    }
    if (target > 0) {
      for (int i = 0; i <= target; i++) {
        dp[i] = 0;
      }
      dp[0] = 1;
      int max_val = x * 2 - 1;
      for (int v = x + 1; v <= max_val; v++) {
        for (int j = target; j >= v; j--) {
          uint64_t ways = dp[j - v];
          dp[j] = dp[j] + ways;
        }
      }
      uint64_t add_ways = dp[target];
      total_ways = total_ways + add_ways;
    }
  }
  std::cout << total_ways << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solve();
  return 0;
}
