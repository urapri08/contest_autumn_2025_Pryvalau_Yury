#include <iostream>
#include <vector>

const long long cInfVal = 2009000999;

struct Edge {
  int to;
  long long weight;
};

struct HeapNode {
  int v;
  long long d;
};

void HeapPush(std::vector<HeapNode>& heap, long long d, int v) {
  heap.push_back({ v, d });
  for (int current_idx = static_cast<int>(heap.size()) - 1; current_idx > 0; ) {
    int parent_idx = (current_idx - 1) / 2;
    if (heap[current_idx].d < heap[parent_idx].d) {
      std::swap(heap[current_idx], heap[parent_idx]);
      current_idx = parent_idx;
    }
    else {
      break;
    }
  }
}

HeapNode HeapPop(std::vector<HeapNode>& heap) {
  HeapNode top_node = heap[0];
  heap[0] = heap.back();
  heap.pop_back();
  int size = static_cast<int>(heap.size());
  for (int current_idx = 0; current_idx < size; ) {
    int left_child = current_idx * 2 + 1;
    int right_child = current_idx * 2 + 2;
    int smallest = current_idx;
    if (left_child < size && heap[left_child].d < heap[smallest].d) {
      smallest = left_child;
    }
    if (right_child < size && heap[right_child].d < heap[smallest].d) {
      smallest = right_child;
    }
    if (smallest != current_idx) {
      std::swap(heap[current_idx], heap[smallest]);
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
    for (const auto& edge : adj[u]) {
      if (current_d + edge.weight < dist[edge.to]) {
        dist[edge.to] = current_d + edge.weight;
        HeapPush(heap, dist[edge.to], edge.to);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases = 0;
  std::cin >> test_cases;
  for (int t_index = 0; t_index < test_cases; ++t_index) {
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<Edge>> adj(n);
    for (int edge_index = 0; edge_index < m; ++edge_index) {
      int u = 0;
      int v = 0;
      long long w = 0;
      std::cin >> u >> v >> w;
      adj[u].push_back({ v, w });
      adj[v].push_back({ u, w });
    }
    int start_node = 0;
    std::cin >> start_node;
    std::vector<long long> dist(n, cInfVal);
    RunDijkstraFast(start_node, adj, dist);
    for (int i = 0; i < n; ++i) {
      std::cout << dist[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << "\n";
  }
  return 0;
}