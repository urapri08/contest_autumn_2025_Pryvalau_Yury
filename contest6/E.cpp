#include <iostream>
#include <vector>

struct Edge {
  int to;
  int id;
};

void QuickSort(std::vector<int>& arr, int left, int right) {
  if (left >= right) {
    return;
  }
  int pivot_index = left + (right - left) / 2;
  int pivot = arr[pivot_index];
  int i = left;
  int j = right;
  while (i <= j) {
    while (arr[i] < pivot) {
      i++;
    }
    while (arr[j] > pivot) {
      j--;
    }
    if (i <= j) {
      std::swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }
  QuickSort(arr, left, j);
  QuickSort(arr, i, right);
}

void FindBridges(
  int current_node,
  int parent_edge,
  const std::vector<std::vector<Edge>>& adj,
  std::vector<int>& time_in,
  std::vector<int>& low_time,
  std::vector<int>& bridges) {
  time_in[current_node] = time_in[0];
  low_time[current_node] = time_in[0];
  time_in[0]++;
  for (const auto& edge : adj[current_node]) {
    int next_node = edge.to;
    int edge_id = edge.id;
    if (edge_id == parent_edge) {
      continue;
    }
    if (time_in[next_node] != 0) {
      if (time_in[next_node] < low_time[current_node]) {
        low_time[current_node] = time_in[next_node];
      }
    }
    else {
      FindBridges(next_node, edge_id, adj, time_in, low_time, bridges);
      if (low_time[next_node] < low_time[current_node]) {
        low_time[current_node] = low_time[next_node];
      }
      if (low_time[next_node] > time_in[current_node]) {
        bridges.push_back(edge_id);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int vertex_count = 0;
  int edge_count = 0;
  std::cin >> vertex_count >> edge_count;

  std::vector<std::vector<Edge>> adj(vertex_count + 1);
  for (int edge_index = 1; edge_index <= edge_count; ++edge_index) {
    int from_vertex = 0;
    int to_vertex = 0;
    std::cin >> from_vertex >> to_vertex;
    adj[from_vertex].push_back(Edge{ to_vertex, edge_index });
    adj[to_vertex].push_back(Edge{ from_vertex, edge_index });
  }

  std::vector<int> time_in(vertex_count + 1, 0);
  std::vector<int> low_time(vertex_count + 1, 0);
  std::vector<int> bridges;
  time_in[0] = 1;
  for (int start_node = 1; start_node <= vertex_count; ++start_node) {
    if (time_in[start_node] == 0) {
      FindBridges(start_node, -1, adj, time_in, low_time, bridges);
    }
  }

  int bridges_count = static_cast<int>(bridges.size());
  std::cout << bridges_count << "\n";

  if (bridges_count > 0) {
    QuickSort(bridges, 0, bridges_count - 1);
    for (int i = 0; i < bridges_count; ++i) {
      std::cout << bridges[i] << (i == bridges_count - 1 ? "" : " ");
    }
    std::cout << "\n";
  }

  return 0;
}