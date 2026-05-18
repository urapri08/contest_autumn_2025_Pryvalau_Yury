#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const long long cInf = 1'000'000'000'000'000'000LL;

struct Edge {
  int u;
  int v;
  long long cap;
  long long flow;
};

struct Graph {
  std::vector<std::vector<int>> adj;
  std::vector<Edge> edges;
  std::vector<int> level;
  std::vector<int> ptr;
};

void AddEdge(int u, int v, long long c, Graph& g) {
  g.adj[u].push_back(static_cast<int>(g.edges.size()));
  g.edges.push_back({ u, v, c, 0 });
  g.adj[v].push_back(static_cast<int>(g.edges.size()));
  g.edges.push_back({ v, u, 0, 0 });
}

bool RunBfs(int source, int sink, long long limit, Graph& g) {
  int n = static_cast<int>(g.adj.size()) - 1;
  g.level.assign(n + 1, -1);
  g.level[source] = 0;
  std::queue<int> q;
  q.push(source);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    int sz = static_cast<int>(g.adj[u].size());
    for (int idx = 0; idx < sz; idx++) {
      int e = g.adj[u][idx];
      int v = g.edges[e].v;
      long long rem = g.edges[e].cap - g.edges[e].flow;
      if (rem >= limit) {
        if (g.level[v] == -1) {
          g.level[v] = g.level[u] + 1;
          q.push(v);
        }
      }
    }
  }
  bool is_reached = (g.level[sink] != -1);
  return is_reached;
}

long long RunDfs(int u, int sink, long long pushed, long long limit, Graph& g) {
  if (pushed == 0) {
    return 0;
  }
  if (u == sink) {
    return pushed;
  }
  int sz = static_cast<int>(g.adj[u].size());
  for (; g.ptr[u] < sz; g.ptr[u]++) {
    int e = g.adj[u][g.ptr[u]];
    int v = g.edges[e].v;
    long long rem = g.edges[e].cap - g.edges[e].flow;
    if (g.level[v] == g.level[u] + 1) {
      if (rem >= limit) {
        long long tr = std::min(pushed, rem);
        long long pushed_res = RunDfs(v, sink, tr, limit, g);
        if (pushed_res > 0) {
          g.edges[e].flow += pushed_res;
          int rev_e = e ^ 1;
          g.edges[rev_e].flow -= pushed_res;
          return pushed_res;
        }
      }
    }
  }
  return 0;
}

void RunDinic(int n, int m, int source, int sink, Graph& g, long long max_c) {
  long long max_flow = 0;
  long long limit = 1;
  while (limit <= max_c) {
    limit = limit * 2;
  }
  while (limit > 0) {
    while (RunBfs(source, sink, limit, g)) {
      g.ptr.assign(n + 1, 0);
      while (true) {
        long long pushed = RunDfs(source, sink, cInf, limit, g);
        if (pushed == 0) {
          break;
        }
        max_flow += pushed;
      }
    }
    limit = limit / 2;
  }
  std::cout << max_flow << "\n";
  for (int e = 0; e < m; e++) {
    long long f = g.edges[e * 2].flow;
    std::cout << f << "\n";
  }
}

void SolveTask() {
  int n = 0;
  int m = 0;
  if (!(std::cin >> n >> m)) {
    return;
  }
  Graph g;
  g.adj.resize(n + 1);
  g.level.resize(n + 1);
  g.ptr.resize(n + 1);
  long long max_c = 0;
  for (int j = 0; j < m; j++) {
    int u = 0;
    int v = 0;
    long long c = 0;
    std::cin >> u >> v >> c;
    AddEdge(u, v, c, g);
    max_c = std::max(max_c, c);
  }
  RunDinic(n, m, 1, n, g, max_c);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  SolveTask();
  return 0;
}