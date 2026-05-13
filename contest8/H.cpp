#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
const long long cInf = 1000000000000000000LL;
struct Graph {
  std::vector<std::vector<int>> adj;
  std::vector<int> edge_u;
  std::vector<int> edge_v;
  std::vector<long long> edge_cap;
  std::vector<long long> edge_flow;
  std::vector<int> level;
  std::vector<int> ptr;
};
void AddEdge(int u, int v, long long c, Graph& g) {
  int idx_uv;
  idx_uv = static_cast<int>(g.edge_u.size());
  g.edge_u.push_back(u);
  g.edge_v.push_back(v);
  g.edge_cap.push_back(c);
  g.edge_flow.push_back(0);
  int idx_vu;
  idx_vu = static_cast<int>(g.edge_u.size());
  g.edge_u.push_back(v);
  g.edge_v.push_back(u);
  g.edge_cap.push_back(0);
  g.edge_flow.push_back(0);
  g.adj[u].push_back(idx_uv);
  g.adj[v].push_back(idx_vu);
}
bool RunBfs(int source, int sink, long long limit, Graph& g) {
  int n;
  n = static_cast<int>(g.adj.size()) - 1;
  int i;
  i = 1;
  while (i <= n) {
    g.level[i] = -1;
    i++;
  }
  g.level[source] = 0;
  std::queue<int> q;
  q.push(source);
  while (!q.empty()) {
    int u;
    u = q.front();
    q.pop();
    int sz;
    sz = static_cast<int>(g.adj[u].size());
    int idx;
    idx = 0;
    while (idx < sz) {
      int e;
      e = g.adj[u][idx];
      int v;
      v = g.edge_v[e];
      long long rem;
      rem = g.edge_cap[e] - g.edge_flow[e];
      if (rem >= limit) {
        if (g.level[v] == -1) {
          g.level[v] = g.level[u] + 1;
          q.push(v);
        }
      }
      idx++;
    }
  }
  bool is_reached;
  is_reached = false;
  if (g.level[sink] != -1) {
    is_reached = true;
  }
  return is_reached;
}
long long RunDfs(int u, int sink, long long pushed, long long limit, Graph& g) {
  if (pushed == 0) {
    return 0;
  }
  if (u == sink) {
    return pushed;
  }
  int sz;
  sz = static_cast<int>(g.adj[u].size());
  while (g.ptr[u] < sz) {
    int idx;
    idx = g.ptr[u];
    int e;
    e = g.adj[u][idx];
    int v;
    v = g.edge_v[e];
    long long rem;
    rem = g.edge_cap[e] - g.edge_flow[e];
    if (g.level[v] == g.level[u] + 1) {
      if (rem >= limit) {
        long long tr;
        tr = std::min(pushed, rem);
        long long pushed_res;
        pushed_res = RunDfs(v, sink, tr, limit, g);
        if (pushed_res > 0) {
          g.edge_flow[e] = g.edge_flow[e] + pushed_res;
          int rev_e;
          rev_e = e ^ 1;
          g.edge_flow[rev_e] = g.edge_flow[rev_e] - pushed_res;
          return pushed_res;
        }
      }
    }
    g.ptr[u]++;
  }
  return 0;
}
void RunDinic(int n, int m, int source, int sink, Graph& g, long long max_c) {
  long long max_flow;
  max_flow = 0;
  long long limit;
  limit = 1;
  while (limit <= max_c) {
    limit = limit * 2;
  }
  while (limit > 0) {
    while (RunBfs(source, sink, limit, g)) {
      int i;
      i = 1;
      while (i <= n) {
        g.ptr[i] = 0;
        i++;
      }
      while (true) {
        long long pushed;
        pushed = RunDfs(source, sink, cInf, limit, g);
        if (pushed == 0) {
          break;
        }
        max_flow = max_flow + pushed;
      }
    }
    limit = limit / 2;
  }
  std::cout << max_flow << "\n";
  int e;
  e = 0;
  while (e < m) {
    long long f;
    f = g.edge_flow[e * 2];
    std::cout << f << "\n";
    e++;
  }
}
void SolveTask() {
  int n;
  int m;
  if (!(std::cin >> n >> m)) {
    return;
  }
  Graph g;
  g.adj.resize(n + 1);
  g.level.resize(n + 1);
  g.ptr.resize(n + 1);
  int j;
  j = 0;
  long long max_c;
  max_c = 0;
  while (j < m) {
    int u;
    int v;
    long long c;
    std::cin >> u >> v >> c;
    AddEdge(u, v, c, g);
    max_c = std::max(max_c, c);
    j++;
  }
  RunDinic(n, m, 1, n, g, max_c);
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  SolveTask();
  return 0;
}