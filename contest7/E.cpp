#include <iostream>
#include <vector>
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
  int iter = 1;
  while (iter <= st.n) {
    st.cycle_start = -1;
    int edge_index = 0;
    int edge_count = st.edges.size();
    while (edge_index < edge_count) {
      int u_node = st.edges[edge_index].u;
      int v_node = st.edges[edge_index].v;
      int edge_cost = st.edges[edge_index].cost;
      long long new_dist = st.dist[u_node];
      new_dist += edge_cost;
      if (new_dist < st.dist[v_node]) {
        st.dist[v_node] = new_dist;
        st.parent[v_node] = u_node;
        st.cycle_start = v_node;
      }
      edge_index++;
    }
    iter++;
  }
}
void PrintResult(State& st) {
  if (st.cycle_start == -1) {
    std::cout << "NO\n";
  }
  else {
    std::cout << "YES\n";
    int curr = st.cycle_start;
    int step = 1;
    while (step <= st.n) {
      curr = st.parent[curr];
      step++;
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
    int left = 0;
    int right = cycle.size();
    right--;
    while (left < right) {
      int temp = cycle[left];
      cycle[left] = cycle[right];
      cycle[right] = temp;
      left++;
      right--;
    }
    std::cout << cycle.size() << "\n";
    int print_index = 0;
    int cycle_size = cycle.size();
    while (print_index < cycle_size) {
      std::cout << cycle[print_index];
      std::cout << " ";
      print_index++;
    }
    std::cout << "\n";
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  State st;
  st.n = 0;
  std::cin >> st.n;
  const int cNoEdge = 100000;
  int row = 1;
  while (row <= st.n) {
    int col = 1;
    while (col <= st.n) {
      int weight = 0;
      std::cin >> weight;
      if (weight != cNoEdge) {
        Edge edge;
        edge.u = row;
        edge.v = col;
        edge.cost = weight;
        st.edges.push_back(edge);
      }
      col++;
    }
    row++;
  }
  RunBellmanFord(st);
  PrintResult(st);
  return 0;
}