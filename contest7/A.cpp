#include <iostream>
#include <vector>
struct Edge {
  int to;
  long long weight;
};
struct HeapNode {
  int v;
  long long d;
};
void HeapPush(std::vector<HeapNode>& heap, long long d, int v) {
  HeapNode node;
  node.d = d;
  node.v = v;
  heap.push_back(node);
  int current_idx = heap.size();
  current_idx--;
  while (current_idx > 0) {
    int parent_idx = current_idx - 1;
    parent_idx /= 2;
    if (heap[current_idx].d < heap[parent_idx].d) {
      HeapNode temp = heap[current_idx];
      heap[current_idx] = heap[parent_idx];
      heap[parent_idx] = temp;
      current_idx = parent_idx;
    }
    else {
      break;
    }
  }
}
HeapNode HeapPop(std::vector<HeapNode>& heap) {
  HeapNode top_node = heap[0];
  int last_idx = heap.size();
  last_idx--;
  heap[0] = heap[last_idx];
  heap.pop_back();
  int current_idx = 0;
  int size = heap.size();
  while (current_idx < size) {
    int left_child = current_idx * 2;
    left_child++;
    int right_child = current_idx * 2;
    right_child += 2;
    int smallest = current_idx;
    if (left_child < size) {
      if (heap[left_child].d < heap[smallest].d) {
        smallest = left_child;
      }
    }
    if (right_child < size) {
      if (heap[right_child].d < heap[smallest].d) {
        smallest = right_child;
      }
    }
    if (smallest != current_idx) {
      HeapNode temp = heap[current_idx];
      heap[current_idx] = heap[smallest];
      heap[smallest] = temp;
      current_idx = smallest;
    }
    else {
      break;
    }
  }
  return top_node;
}
void RunDijkstraFast(int start_node, const std::vector<std::vector<Edge>>& adj,
  std::vector<long long>& dist) {
  std::vector<HeapNode> heap;
  dist[start_node] = 0;
  HeapPush(heap, 0, start_node);
  while (!heap.empty()) {
    HeapNode current = HeapPop(heap);
    int u = current.v;
    long long current_d = current.d;
    if (current_d > dist[u]) {
      continue;
    }
    int neighbor_count = adj[u].size();
    int neighbor_index = 0;
    while (neighbor_index < neighbor_count) {
      int next_node = adj[u][neighbor_index].to;
      long long edge_weight = adj[u][neighbor_index].weight;
      long long new_dist = current_d;
      new_dist += edge_weight;
      if (new_dist < dist[next_node]) {
        dist[next_node] = new_dist;
        HeapPush(heap, new_dist, next_node);
      }
      neighbor_index++;
    }
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int test_cases = 0;
  std::cin >> test_cases;
  int t_index = 0;
  while (t_index < test_cases) {
    int n = 0;
    int m = 0;
    std::cin >> n;
    std::cin >> m;
    std::vector<std::vector<Edge>> adj(n);
    int edge_index = 0;
    while (edge_index < m) {
      int u = 0;
      int v = 0;
      long long w = 0;
      std::cin >> u;
      std::cin >> v;
      std::cin >> w;
      Edge forward_edge;
      forward_edge.to = v;
      forward_edge.weight = w;
      adj[u].push_back(forward_edge);
      Edge backward_edge;
      backward_edge.to = u;
      backward_edge.weight = w;
      adj[v].push_back(backward_edge);
      edge_index++;
    }
    int start_node = 0;
    std::cin >> start_node;
    const long long cInfVal = 2009000999;
    std::vector<long long> dist(n, cInfVal);
    RunDijkstraFast(start_node, adj, dist);
    int print_index = 0;
    while (print_index < n) {
      std::cout << dist[print_index];
      std::cout << " ";
      print_index++;
    }
    std::cout << "\n";
    t_index++;
  }
  return 0;
}