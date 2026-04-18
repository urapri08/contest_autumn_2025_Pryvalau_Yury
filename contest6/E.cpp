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
  int pivot_index = right - left;
  pivot_index /= 2;
  pivot_index += left;
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
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
      i++;
      j--;
    }
  }
  QuickSort(arr, left, j);
  QuickSort(arr, i, right);
}
void FindBridges(int current_node, int parent_edge,
  const std::vector<std::vector<Edge>>& adj,
  std::vector<int>& time_in, std::vector<int>& low_time,
  std::vector<int>& bridges) {
  time_in[current_node] = time_in[0];
  low_time[current_node] = time_in[0];
  time_in[0]++;
  int neighbor_count = adj[current_node].size();
  int neighbor_index = 0;
  while (neighbor_index < neighbor_count) {
    int next_node = adj[current_node][neighbor_index].to;
    int edge_id = adj[current_node][neighbor_index].id;
    if (edge_id == parent_edge) {
      neighbor_index++;
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
    neighbor_index++;
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int vertex_count = 0;
  int edge_count = 0;
  std::cin >> vertex_count;
  std::cin >> edge_count;
  std::vector<std::vector<Edge>> adj(vertex_count + 1);
  int edge_index = 1;
  while (edge_index <= edge_count) {
    int from_vertex = 0;
    int to_vertex = 0;
    std::cin >> from_vertex;
    std::cin >> to_vertex;
    Edge forward_edge;
    forward_edge.to = to_vertex;
    forward_edge.id = edge_index;
    adj[from_vertex].push_back(forward_edge);
    Edge backward_edge;
    backward_edge.to = from_vertex;
    backward_edge.id = edge_index;
    adj[to_vertex].push_back(backward_edge);
    edge_index++;
  }
  std::vector<int> time_in(vertex_count + 1, 0);
  std::vector<int> low_time(vertex_count + 1, 0);
  std::vector<int> bridges;
  time_in[0] = 1;
  int start_node = 1;
  while (start_node <= vertex_count) {
    if (time_in[start_node] == 0) {
      FindBridges(start_node, -1, adj, time_in, low_time, bridges);
    }
    start_node++;
  }
  int bridges_count = bridges.size();
  std::cout << bridges_count << "\n";
  if (bridges_count > 0) {
    int max_index = bridges_count - 1;
    QuickSort(bridges, 0, max_index);
    int print_index = 0;
    while (print_index < bridges_count) {
      std::cout << bridges[print_index];
      std::cout << " ";
      print_index++;
    }
    std::cout << "\n";
  }
  return 0;
}