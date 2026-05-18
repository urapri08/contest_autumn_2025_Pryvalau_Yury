#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const long long cInf = 2'000'000'000'000'000'000LL;

bool RunBfs(int source, int sink, int n,
  const std::vector<std::vector<long long>>& capacity,
  std::vector<int>& parent) {
  parent.assign(n + 1, -1);
  std::queue<int> q;
  q.push(source);
  parent[source] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (u == sink) {
      return true;
    }

    for (int v = 1; v <= n; ++v) {
      if (parent[v] == -1 && capacity[u][v] > 0) {
        parent[v] = u;
        q.push(v);
      }
    }
  }

  return false;
}

void PushFlow(int n, std::vector<std::vector<long long>>& capacity,
  const std::vector<int>& parent) {
  long long push_flow = cInf;
  for (int curr = n; curr != 1; curr = parent[curr]) {
    push_flow = std::min(push_flow, capacity[parent[curr]][curr]);
  }

  for (int curr = n; curr != 1; curr = parent[curr]) {
    int prev = parent[curr];
    capacity[prev][curr] -= push_flow;
    capacity[curr][prev] += push_flow;
  }
}

void RunEdmondsKarp(int n, std::vector<std::vector<long long>>& capacity) {
  std::vector<int> parent(n + 1);
  while (RunBfs(1, n, n, capacity, parent)) {
    PushFlow(n, capacity, parent);
  }
}

void FindCut(int source, int n,
  const std::vector<std::vector<long long>>& capacity,
  std::vector<bool>& visited) {
  visited.assign(n + 1, false);
  std::queue<int> q;
  q.push(source);
  visited[source] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 1; v <= n; ++v) {
      if (!visited[v] && capacity[u][v] > 0) {
        visited[v] = true;
        q.push(v);
      }
    }
  }
}

void ReadGraph(int m, std::vector<std::vector<long long>>& capacity,
  std::vector<int>& edge_u, std::vector<int>& edge_v,
  std::vector<long long>& edge_c) {
  for (int j = 0; j < m; ++j) {
    std::cin >> edge_u[j] >> edge_v[j] >> edge_c[j];
    capacity[edge_u[j]][edge_v[j]] += edge_c[j];
    capacity[edge_v[j]][edge_u[j]] += edge_c[j];
  }
}

void PrintCut(int m, const std::vector<int>& edge_u, const std::vector<int>& edge_v,
  const std::vector<long long>& edge_c, const std::vector<bool>& visited) {
  std::vector<int> cut_edges;
  long long cut_weight = 0;

  for (int e = 0; e < m; ++e) {
    if (visited[edge_u[e]] != visited[edge_v[e]]) {
      cut_edges.push_back(e + 1);
      cut_weight += edge_c[e];
    }
  }

  std::cout << cut_edges.size() << " " << cut_weight << "\n";
  for (int k = 0; k < static_cast<int>(cut_edges.size()); ++k) {
    if (k > 0) {
      std::cout << " ";
    }
    std::cout << cut_edges[k];
  }
  std::cout << "\n";
}

void SolveTask() {
  int n = 0;
  int m = 0;
  if (!(std::cin >> n >> m)) {
    return;
  }

  std::vector<std::vector<long long>> capacity(n + 1, std::vector<long long>(n + 1, 0));
  std::vector<int> edge_u(m);
  std::vector<int> edge_v(m);
  std::vector<long long> edge_c(m);

  ReadGraph(m, capacity, edge_u, edge_v, edge_c);
  RunEdmondsKarp(n, capacity);

  std::vector<bool> visited(n + 1, false);
  FindCut(1, n, capacity, visited);
  PrintCut(m, edge_u, edge_v, edge_c, visited);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  SolveTask();
  return 0;
}