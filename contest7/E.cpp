#include <algorithm>
#include <iostream>
#include <vector>

const int cNoEdge = 100000;

struct Edge {
  int u;
  int v;
  int cost;
};

struct State {
  std::vector<Edge> edges;
  std::vector<long long> dist;
  std::vector<int> parent;
  int n;
  int cycle_start;
};

void RunBellmanFord(State& st) {
  st.dist.assign(st.n + 1, 0);
  st.parent.assign(st.n + 1, -1);
  st.cycle_start = -1;

  for (int iter = 1; iter <= st.n; ++iter) {
    st.cycle_start = -1;
    for (const auto& edge : st.edges) {
      if (st.dist[edge.u] + edge.cost < st.dist[edge.v]) {
        st.dist[edge.v] = st.dist[edge.u] + edge.cost;
        st.parent[edge.v] = edge.u;
        st.cycle_start = edge.v;
      }
    }
  }
}

void PrintResult(State& st) {
  if (st.cycle_start == -1) {
    std::cout << "NO\n";
  }
  else {
    std::cout << "YES\n";
    int curr = st.cycle_start;
    for (int step = 1; step <= st.n; ++step) {
      curr = st.parent[curr];
    }

    std::vector<int> cycle;
    int start_node = curr;
    cycle.push_back(start_node);
    curr = st.parent[start_node];
    while (curr != start_node) {
      cycle.push_back(curr);
      curr = st.parent[curr];
    }
    cycle.push_back(start_node);
    std::reverse(cycle.begin(), cycle.end());

    std::cout << cycle.size() << "\n";
    for (int i = 0; i < static_cast<int>(cycle.size()); ++i) {
      std::cout << cycle[i] << (i == static_cast<int>(cycle.size()) - 1 ? "" : " ");
    }
    std::cout << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  if (!(std::cin >> n)) {
    return 0;
  }

  State st;
  st.n = n;
  for (int row = 1; row <= st.n; ++row) {
    for (int col = 1; col <= st.n; ++col) {
      int weight = 0;
      std::cin >> weight;
      if (weight != cNoEdge) {
        st.edges.push_back({ row, col, weight });
      }
    }
  }

  RunBellmanFord(st);
  PrintResult(st);

  return 0;
}