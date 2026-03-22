#include <iostream>
#include <string>
#include <vector>
const int cZero = 0;
const int cOne = 1;
const int cMinusOne = -1;
const int cInf = 10'000;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string u;
  std::cin >> u;
  std::string v;
  std::cin >> v;
  int k = cZero;
  std::cin >> k;
  int m = (int)u.length();
  int n = (int)v.length();
  std::vector<std::vector<std::vector<int>>> dp(n + cOne, std::vector<std::vector<int>>(m + cOne, std::vector<int>(k + cOne, cInf)));
  dp[cZero][cZero][cZero] = cZero;
  for (int i = cZero; i <= n; i++) {
    for (int j = cZero; j <= m; j++) {
      for (int d = cZero; d <= k; d++) {
        int val = dp[i][j][d];
        if (val == cInf) {
          continue;
        }
        if (i < n) {
          if (d + cOne <= k) {
            if (val < dp[i + cOne][j][d + cOne]) {
              dp[i + cOne][j][d + cOne] = val;
            }
          }
        }
        if (j < m) {
          if (d + cOne <= k) {
            if (val < dp[i][j + cOne][d + cOne]) {
              dp[i][j + cOne][d + cOne] = val;
            }
          }
        }
        if (i < n) {
          if (j < m) {
            if (d + cOne <= k) {
              if (val < dp[i + cOne][j + cOne][d + cOne]) {
                dp[i + cOne][j + cOne][d + cOne] = val;
              }
            }
            int cost = cOne;
            if (v[i] == u[j]) {
              cost = cZero;
            }
            if (val + cost < dp[i + cOne][j + cOne][d]) {
              dp[i + cOne][j + cOne][d] = val + cost;
            }
          }
        }
      }
    }
  }
  int ans = cInf;
  for (int d = cZero; d <= k; d++) {
    if (dp[n][m][d] < ans) {
      ans = dp[n][m][d];
    }
  }
  if (ans == cInf) {
    std::cout << cMinusOne << '\n';
  }
  else {
    std::cout << ans << '\n';
  }
  return cZero;
}