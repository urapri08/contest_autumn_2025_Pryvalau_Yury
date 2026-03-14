#include <iostream>
#include <string>
const int cMaxN = 1005;
const int cMaxK = 25;
const int cInf = 10000;
int dp[cMaxN][cMaxN][cMaxK];
std::string global_u;
std::string global_v;
int global_n;
int global_m;
int global_k;
void InitDP() {
  int i;
  i = 0;
  while (i <= global_n) {
    int j;
    j = 0;
    while (j <= global_m) {
      int d;
      d = 0;
      while (d <= global_k) {
        dp[i][j][d] = cInf;
        d++;
      }
      j++;
    }
    i++;
  }
  dp[0][0][0] = 0;
}
void ProcessInsert(int i, int j, int d, int val) {
  if (i < global_n) {
    if (d + 1 <= global_k) {
      if (val < dp[i + 1][j][d + 1]) {
        dp[i + 1][j][d + 1] = val;
      }
    }
  }
}
void ProcessDelete(int i, int j, int d, int val) {
  if (j < global_m) {
    if (d + 1 <= global_k) {
      if (val < dp[i][j + 1][d + 1]) {
        dp[i][j + 1][d + 1] = val;
      }
    }
  }
}
void ProcessMatchSub(int i, int j, int d, int val) {
  if (i < global_n) {
    if (j < global_m) {
      if (d + 1 <= global_k) {
        if (val < dp[i + 1][j + 1][d + 1]) {
          dp[i + 1][j + 1][d + 1] = val;
        }
      }
      int cost;
      cost = 1;
      if (global_v[i] == global_u[j]) {
        cost = 0;
      }
      if (val + cost < dp[i + 1][j + 1][d]) {
        dp[i + 1][j + 1][d] = val + cost;
      }
    }
  }
}
void ProcessState(int i, int j, int d) {
  int val;
  val = dp[i][j][d];
  if (val == cInf) {
    return;
  }
  ProcessInsert(i, j, d, val);
  ProcessDelete(i, j, d, val);
  ProcessMatchSub(i, j, d, val);
}
void RunDP() {
  int i;
  i = 0;
  while (i <= global_n) {
    int j;
    j = 0;
    while (j <= global_m) {
      int d;
      d = 0;
      while (d <= global_k) {
        ProcessState(i, j, d);
        d++;
      }
      j++;
    }
    i++;
  }
}
void PrintAnswer() {
  int ans;
  ans = cInf;
  int d;
  d = 0;
  while (d <= global_k) {
    if (dp[global_n][global_m][d] < ans) {
      ans = dp[global_n][global_m][d];
    }
    d++;
  }
  if (ans == cInf) {
    std::cout << -1 << "\n";
  }
  else {
    std::cout << ans << "\n";
  }
}
void Solve() {
  std::cin >> global_u;
  std::cin >> global_v;
  std::cin >> global_k;
  global_m = (int)global_u.length();
  global_n = (int)global_v.length();
  InitDP();
  RunDP();
  PrintAnswer();
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Solve();
  return 0;
}