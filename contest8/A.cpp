#include <iostream>
#include <vector>
const int cZero = 0;
const int cOne = 1;
const int cMinusOne = -1;
bool DfsKuhn(int current_node, const std::vector<std::vector<int>>& adj,
  std::vector<int>& used, std::vector<int>& mt) {
  if (used[current_node] == cOne) {
    return false;
  }
  used[current_node] = cOne;
  int neighbor_count = adj[current_node].size();
  int neighbor_index = cZero;
  while (neighbor_index < neighbor_count) {
    int next_node = adj[current_node][neighbor_index];
    if (mt[next_node] == cMinusOne) {
      mt[next_node] = current_node;
      return true;
    }
    bool can_shift;
    can_shift = DfsKuhn(mt[next_node], adj, used, mt);
    if (can_shift) {
      mt[next_node] = current_node;
      return true;
    }
    neighbor_index++;
  }
  return false;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n_left = cZero;
  int k_right = cZero;
  if (!(std::cin >> n_left >> k_right)) {
    return cZero;
  }
  std::vector<std::vector<int>> adjacency_list(n_left + cOne);
  int current_left = cOne;
  while (current_left <= n_left) {
    int to_vertex = cZero;
    while (true) {
      std::cin >> to_vertex;
      if (to_vertex == cZero) {
        break;
      }
      adjacency_list[current_left].push_back(to_vertex);
    }
    current_left++;
  }
  std::vector<int> match_table(k_right + cOne, cMinusOne);
  std::vector<int> used_nodes(n_left + cOne, cZero);
  int candidate = cOne;
  while (candidate <= n_left) {
    int reset_index = cOne;
    while (reset_index <= n_left) {
      used_nodes[reset_index] = cZero;
      reset_index++;
    }
    DfsKuhn(candidate, adjacency_list, used_nodes, match_table);
    candidate++;
  }
  int match_count = cZero;
  int check_right = cOne;
  while (check_right <= k_right) {
    if (match_table[check_right] != cMinusOne) {
      match_count++;
    }
    check_right++;
  }
  std::cout << match_count << "\n";
  int print_right = cOne;
  while (print_right <= k_right) {
    if (match_table[print_right] != cMinusOne) {
      std::cout << match_table[print_right];
      std::cout << " ";
      std::cout << print_right;
      std::cout << "\n";
    }
    print_right++;
  }
  return cZero;
}