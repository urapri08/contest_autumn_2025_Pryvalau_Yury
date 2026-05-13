#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int u;
  int v;
  long long weight;

  bool operator<(const Edge& other) const {
    return weight < other.weight;
  }
};

struct Dsu {
  std::vector<int> parent;
  std::vector<int> sz_val;

  Dsu(int n) : parent(n + 1), sz_val(n + 1, 1) {
    for (int i = 1; i <= n; ++i) {
      parent[i] = i;
    }
  }

  int FindSet(int v) {
    if (v == parent[v]) {
      return v;
    }
    return parent[v] = FindSet(parent[v]);
  }

  bool UnionSets(int a, int b) {
    int root_a = FindSet(a);
    int root_b = FindSet(b);
    if (root_a != root_b) {
      if (sz_val[root_a] < sz_val[root_b]) {
        std::swap(root_a, root_b);
      }
      parent[root_b] = root_a;
      sz_val[root_a] += sz_val[root_b];
      return true;
    }
    return false;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n_val = 0;
  int m_val = 0;
  if (!(std::cin >> n_val >> m_val)) {
    return 0;
  }

  std::vector<Edge> edges;
  for (int i = 0; i < m_val; ++i) {
    int u = 0;
    int v = 0;
    long long w = 0;
    std::cin >> u >> v >> w;
    edges.push_back({ u, v, w });
  }

  std::sort(edges.begin(), edges.end());

  Dsu dsu(n_val);
  long long total_weight = 0;
  for (const auto& edge : edges) {
    if (dsu.UnionSets(edge.u, edge.v)) {
      total_weight += edge.weight;
    }
  }

  std::cout << total_weight << "\n";

  return 0;
}