#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
const long long cInf = 2000000000000000000LL;
bool RunBfs(int source, int sink, int n,
  const std::vector<std::vector<long long>>& capacity,
  std::vector<int>& parent) {
  int i;
  i = 1;
  while (i <= n) {
    parent[i] = -1;
    i++;
  }
  std::queue<int> q;
  q.push(source);
  parent[source] = 0;
  while (!q.empty()) {
    int u;
    u = q.front();
    q.pop();
    if (u == sink) {
      return true;
    }
    int v;
    v = 1;
    while (v <= n) {
      if (parent[v] == -1) {
        if (capacity[u][v] > 0) {
          parent[v] = u;
          q.push(v);
        }
      }
      v++;
    }
  }
  return false;
}
void PushFlow(int n, std::vector<std::vector<long long>>& capacity,
  const std::vector<int>& parent) {
  long long push_flow;
  push_flow = cInf;
  int curr;
  curr = n;
  while (curr != 1) {
    int prev;
    prev = parent[curr];
    push_flow = std::min(push_flow, capacity[prev][curr]);
    curr = prev;
  }
  curr = n;
  while (curr != 1) {
    int prev;
    prev = parent[curr];
    capacity[prev][curr] = capacity[prev][curr] - push_flow;
    capacity[curr][prev] = capacity[curr][prev] + push_flow;
    curr = prev;
  }
}
void RunEdmondsKarp(int n, std::vector<std::vector<long long>>& capacity) {
  std::vector<int> parent;
  parent.resize(n + 1);
  while (true) {
    bool has_path;
    has_path = RunBfs(1, n, n, capacity, parent);
    if (!has_path) {
      break;
    }
    PushFlow(n, capacity, parent);
  }
}
void FindCut(int source, int n,
  const std::vector<std::vector<long long>>& capacity,
  std::vector<bool>& visited) {
  int i;
  i = 1;
  while (i <= n) {
    visited[i] = false;
    i++;
  }
  std::queue<int> q;
  q.push(source);
  visited[source] = true;
  while (!q.empty()) {
    int u;
    u = q.front();
    q.pop();
    int v;
    v = 1;
    while (v <= n) {
      if (!visited[v]) {
        if (capacity[u][v] > 0) {
          visited[v] = true;
          q.push(v);
        }
      }
      v++;
    }
  }
}
void SolveTask() {
  int n;
  int m;
  if (!(std::cin >> n >> m)) {
    return;
  }
  std::vector<std::vector<long long>> capacity;
  capacity.resize(n + 1);
  int i;
  i = 0;
  while (i <= n) {
    capacity[i].resize(n + 1, 0);
    i++;
  }
  std::vector<int> edge_u;
  edge_u.resize(m);
  std::vector<int> edge_v;
  edge_v.resize(m);
  std::vector<long long> edge_c;
  edge_c.resize(m);
  int j;
  j = 0;
  while (j < m) {
    std::cin >> edge_u[j] >> edge_v[j] >> edge_c[j];
    int u;
    u = edge_u[j];
    int v;
    v = edge_v[j];
    long long c;
    c = edge_c[j];
    capacity[u][v] = capacity[u][v] + c;
    capacity[v][u] = capacity[v][u] + c;
    j++;
  }
  RunEdmondsKarp(n, capacity);
  std::vector<bool> visited;
  visited.resize(n + 1);
  FindCut(1, n, capacity, visited);
  std::vector<int> cut_edges;
  long long cut_weight;
  cut_weight = 0;
  int e;
  e = 0;
  while (e < m) {
    int u;
    u = edge_u[e];
    int v;
    v = edge_v[e];
    bool diff;
    diff = false;
    if (visited[u]) {
      if (!visited[v]) {
        diff = true;
      }
    }
    if (!visited[u]) {
      if (visited[v]) {
        diff = true;
      }
    }
    if (diff) {
      cut_edges.push_back(e + 1);
      cut_weight = cut_weight + edge_c[e];
    }
    e++;
  }
  std::cout << cut_edges.size() << " " << cut_weight << "\n";
  int sz;
  sz = static_cast<int>(cut_edges.size());
  int k;
  k = 0;
  while (k < sz) {
    if (k > 0) {
      std::cout << " ";
    }
    std::cout << cut_edges[k];
    k++;
  }
  std::cout << "\n";
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  SolveTask();
  return 0;
}