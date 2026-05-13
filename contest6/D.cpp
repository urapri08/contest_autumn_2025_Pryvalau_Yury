#include <iostream>
#include <vector>

void DfsFirstPass(int current_node,
  const std::vector<std::vector<int>>& adjacency_list,
  std::vector<int>& visited_nodes,
  std::vector<int>& exit_order) {
  visited_nodes[current_node] = 1;
  for (int next_node : adjacency_list[current_node]) {
    if (visited_nodes[next_node] == 0) {
      DfsFirstPass(next_node, adjacency_list, visited_nodes, exit_order);
    }
  }
  exit_order.push_back(current_node);
}

void DfsSecondPass(int current_node,
  const std::vector<std::vector<int>>& reversed_graph,
  std::vector<int>& component_ids, int current_id) {
  component_ids[current_node] = current_id;
  for (int next_node : reversed_graph[current_node]) {
    if (component_ids[next_node] == 0) {
      DfsSecondPass(next_node, reversed_graph, component_ids, current_id);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int vertex_count = 0;
  int edge_count = 0;
  std::cin >> vertex_count >> edge_count;

  std::vector<std::vector<int>> adjacency_list(vertex_count + 1);
  std::vector<std::vector<int>> reversed_graph(vertex_count + 1);

  for (int i = 0; i < edge_count; ++i) {
    int from_vertex = 0;
    int to_vertex = 0;
    std::cin >> from_vertex >> to_vertex;
    adjacency_list[from_vertex].push_back(to_vertex);
    reversed_graph[to_vertex].push_back(from_vertex);
  }

  std::vector<int> visited_nodes(vertex_count + 1, 0);
  std::vector<int> exit_order;
  for (int i = 1; i <= vertex_count; ++i) {
    if (visited_nodes[i] == 0) {
      DfsFirstPass(i, adjacency_list, visited_nodes, exit_order);
    }
  }

  std::vector<int> component_ids(vertex_count + 1, 0);
  int current_id = 0;
  for (int i = vertex_count - 1; i >= 0; --i) {
    int check_node = exit_order[i];
    if (component_ids[check_node] == 0) {
      current_id++;
      DfsSecondPass(check_node, reversed_graph, component_ids, current_id);
    }
  }

  std::cout << current_id << "\n";
  for (int i = 1; i <= vertex_count; ++i) {
    std::cout << component_ids[i] << (i == vertex_count ? "" : " ");
  }
  std::cout << "\n";

  return 0;
}
