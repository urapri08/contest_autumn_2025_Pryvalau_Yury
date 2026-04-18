#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int u;
  int v;
  long long weight;
  bool operator<(const Edge& other) const { return weight < other.weight; }
};

struct Dsu {
  std::vector<int> parent;
  std::vector<int> sz_val;
};

void InitDsu(Dsu& dsu, int n) {
  dsu.parent.resize(n + 1);
  dsu.sz_val.assign(n + 1, 1);
  int idx = 1;
  while (idx <= n) {
    dsu.parent[idx] = idx;
    idx++;
  }
}

int FindSet(Dsu& dsu, int v) {
  if (v == dsu.parent[v]) {
    return v;
  }
  dsu.parent[v] = FindSet(dsu, dsu.parent[v]);
  return dsu.parent[v];
}

bool UnionSets(Dsu& dsu, int a, int b) {
  int root_a = FindSet(dsu, a);
  int root_b = FindSet(dsu, b);
  if (root_a != root_b) {
    if (dsu.sz_val[root_a] < dsu.sz_val[root_b]) {
      int temp = root_a;
      root_a = root_b;
      root_b = temp;
    }
    dsu.parent[root_b] = root_a;
    dsu.sz_val[root_a] += dsu.sz_val[root_b];
    return true;
  }
  return false;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n_val = 0;
  int m_val = 0;
  std::cin >> n_val >> m_val;
  std::vector<Edge> edges;
  int m_idx = 0;
  while (m_idx < m_val) {
    int u = 0;
    int v = 0;
    long long w = 0;
    std::cin >> u >> v >> w;
    Edge e;
    e.u = u;
    e.v = v;
    e.weight = w;
    edges.push_back(e);
    m_idx++;
  }
  std::sort(edges.begin(), edges.end());
  Dsu dsu;
  InitDsu(dsu, n_val);
  long long total_weight = 0;
  int e_idx = 0;
  int sz = static_cast<int>(edges.size());
  while (e_idx < sz) {
    if (UnionSets(dsu, edges[e_idx].u, edges[e_idx].v)) {
      total_weight += edges[e_idx].weight;
    }
    e_idx++;
  }
  std::cout << total_weight << "\n";
  return 0;
}