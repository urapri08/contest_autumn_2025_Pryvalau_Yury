#include <iostream>
#include <string>
#include <vector>

struct Node {
  int64_t val;
  int32_t rid;
};

void SiftUp(std::vector<Node>& heap, std::vector<int32_t>& heap_pos, int32_t u) {
  if (u == 1) {
    return;
  }
  int32_t p = u / 2;
  if (heap[p].val > heap[u].val) {
    heap_pos[heap[u].rid] = p;
    heap_pos[heap[p].rid] = u;
    std::swap(heap[u], heap[p]);
    SiftUp(heap, heap_pos, p);
  }
}

void SiftDown(std::vector<Node>& heap, std::vector<int32_t>& heap_pos, int32_t p) {
  int32_t n = heap.size();
  int32_t u = 2 * p;
  if (u >= n) {
    return;
  }
  if (u + 1 < n && heap[u + 1].val < heap[u].val) {
    u++;
  }
  if (heap[u].val < heap[p].val) {
    heap_pos[heap[u].rid] = p;
    heap_pos[heap[p].rid] = u;
    std::swap(heap[u], heap[p]);
    SiftDown(heap, heap_pos, u);
  }
}

void HInsert(std::vector<Node>& heap, std::vector<int32_t>& heap_pos, int64_t x,
  int32_t rid) {
  heap.push_back({ x, rid });
  heap_pos[rid] = heap.size() - 1;
  SiftUp(heap, heap_pos, heap.size() - 1);
}

int64_t GetMin(const std::vector<Node>& heap) { return heap[1].val; }

void ExtractMin(std::vector<Node>& heap, std::vector<int32_t>& heap_pos) {
  if (heap.size() <= 1) {
    return;
  }
  int32_t last_idx = heap.size() - 1;
  heap_pos[heap[1].rid] = last_idx;
  heap_pos[heap[last_idx].rid] = 1;
  std::swap(heap[1], heap[last_idx]);
  heap_pos[heap[last_idx].rid] = 0;
  heap.pop_back();
  SiftDown(heap, heap_pos, 1);
}

void UpdateKey(std::vector<Node>& heap, std::vector<int32_t>& heap_pos, int32_t rid,
  int64_t delta) {
  int32_t current_idx = heap_pos[rid];
  if (current_idx == 0) {
    return;
  }
  heap[current_idx].val -= delta;
  SiftUp(heap, heap_pos, current_idx);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::vector<Node> heap(1);
  int32_t q;
  std::cin >> q;
  std::vector<int32_t> heap_pos;
  heap_pos.resize(q + 1);
  std::string command;
  int64_t val;
  int32_t rid;
  for (int32_t i = 1; i <= q; ++i) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> val;
      HInsert(heap, heap_pos, val, i);
    }
    else if (command == "getMin") {
      std::cout << GetMin(heap) << "\n";
    }
    else if (command == "extractMin") {
      ExtractMin(heap, heap_pos);
    }
    else if (command == "decreaseKey") {
      std::cin >> rid >> val;
      UpdateKey(heap, heap_pos, rid, val);
    }
  }
  return 0;
}



