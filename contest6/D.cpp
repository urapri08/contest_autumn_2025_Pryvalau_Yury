#include <iostream>
#include <vector>
const int cZero = 0;
const int cOne = 1;
void DfsFirstPass(int current_node,
  const std::vector<std::vector<int>>& adjacency_list,
  std::vector<int>& visited_nodes,
  std::vector<int>& exit_order) {
  visited_nodes[current_node] = cOne;
  int neighbor_count = adjacency_list[current_node].size();
  int neighbor_index = cZero;
  while (neighbor_index < neighbor_count) {
    int next_node = adjacency_list[current_node][neighbor_index];
    if (visited_nodes[next_node] == cZero) {
      DfsFirstPass(next_node, adjacency_list, visited_nodes, exit_order);
    }
    neighbor_index++;
  }
  exit_order.push_back(current_node);
}
void DfsSecondPass(int current_node,
  const std::vector<std::vector<int>>& reversed_graph,
  std::vector<int>& component_ids, int current_id) {
  component_ids[current_node] = current_id;
  int neighbor_count = reversed_graph[current_node].size();
  int neighbor_index = cZero;
  while (neighbor_index < neighbor_count) {
    int next_node = reversed_graph[current_node][neighbor_index];
    if (component_ids[next_node] == cZero) {
      DfsSecondPass(next_node, reversed_graph, component_ids, current_id);
    }
    neighbor_index++;
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int vertex_count = cZero;
  int edge_count = cZero;
  std::cin >> vertex_count;
  std::cin >> edge_count;
  std::vector<std::vector<int>> adjacency_list(vertex_count + cOne);
  std::vector<std::vector<int>> reversed_graph(vertex_count + cOne);
  int edge_index = cZero;
  while (edge_index < edge_count) {
    int from_vertex = cZero;
    int to_vertex = cZero;
    std::cin >> from_vertex;
    std::cin >> to_vertex;
    adjacency_list[from_vertex].push_back(to_vertex);
    reversed_graph[to_vertex].push_back(from_vertex);
    edge_index++;
  }
  std::vector<int> visited_nodes(vertex_count + cOne, cZero);
  std::vector<int> exit_order;
  int start_node = cOne;
  while (start_node <= vertex_count) {
    if (visited_nodes[start_node] == cZero) {
      DfsFirstPass(start_node, adjacency_list, visited_nodes, exit_order);
    }
    start_node++;
  }
  std::vector<int> component_ids(vertex_count + cOne, cZero);
  int current_id = cZero;
  int order_index = exit_order.size();
  order_index--;
  while (order_index >= cZero) {
    int check_node = exit_order[order_index];
    if (component_ids[check_node] == cZero) {
      current_id++;
      DfsSecondPass(check_node, reversed_graph, component_ids, current_id);
    }
    order_index--;
  }
  std::cout << current_id << "\n";
  int print_node = cOne;
  while (print_node <= vertex_count) {
    std::cout << component_ids[print_node];
    std::cout << " ";
    print_node++;
  }
  std::cout << "\n";
  return cZero;
}