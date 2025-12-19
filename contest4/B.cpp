#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

const int32_t cMaxNodes = 300'005;

struct Node {
  int64_t key;
  int32_t left;
  int32_t right;
  int32_t parent;
  int32_t size;

  Node() : key(0), left(0), right(0), parent(0), size(0) {}

  Node(int64_t k) : key(k), left(0), right(0), parent(0), size(1) {}
};

class SplayTree {
private:
  std::vector<Node> nodes;
  int32_t root;

  void UpdateSize(int32_t t) {
    if (t != 0) {
      nodes[t].size = 1;
      if (nodes[t].left != 0) {
        nodes[t].size = nodes[t].size + nodes[nodes[t].left].size;
      }
      if (nodes[t].right != 0) {
        nodes[t].size = nodes[t].size + nodes[nodes[t].right].size;
      }
    }
  }

  void Rotate(int32_t t) {
    int32_t p = nodes[t].parent;
    int32_t g = nodes[p].parent;
    int32_t child;

    if (nodes[p].left == t) {
      child = nodes[t].right;
      nodes[p].left = child;
      nodes[t].right = p;
    }
    else {
      child = nodes[t].left;
      nodes[p].right = child;
      nodes[t].left = p;
    }
    if (child != 0) {
      nodes[child].parent = p;
    }
    nodes[t].parent = g;
    nodes[p].parent = t;
    if (g != 0) {
      if (nodes[g].left == p) {
        nodes[g].left = t;
      }
      else {
        nodes[g].right = t;
      }
    }
    else {
      root = t;
    }
    UpdateSize(p);
    UpdateSize(t);
  }

  void Splay(int32_t t) {
    while (nodes[t].parent != 0) {
      int32_t p = nodes[t].parent;
      int32_t g = nodes[p].parent;
      if (g != 0) {
        if ((nodes[p].left == t) == (nodes[g].left == p)) {
          Rotate(p);
        }
        else {
          Rotate(t);
        }
      }
      Rotate(t);
    }
  }

  int32_t Find(int64_t key) {
    if (root == 0) {
      return 0;
    }
    int32_t cur = root;
    int32_t last = 0;

    while (cur != 0) {
      if (nodes[cur].key == key) {
        Splay(cur);
        return cur;
      }
      last = cur;
      if (key < nodes[cur].key) {
        cur = nodes[cur].left;
      }
      else {
        cur = nodes[cur].right;
      }
    }

    Splay(last);
    return last;
  }

public:
  SplayTree() : root(0) {
    nodes.reserve(cMaxNodes);
    nodes.push_back(Node());
  }

  void Insert(int64_t key) {
    if (root == 0) {
      nodes.emplace_back(key);
      root = (int32_t)nodes.size() - 1;
      return;
    }

    int32_t t = Find(key);
    if (nodes[t].key == key) {
      return;
    }

    nodes.emplace_back(key);
    int32_t new_node = (int32_t)nodes.size() - 1;

    if (key < nodes[t].key) {
      nodes[new_node].left = nodes[t].left;
      nodes[new_node].right = t;
      if (nodes[new_node].left != 0) {
        nodes[nodes[new_node].left].parent = new_node;
      }
      nodes[t].left = 0;
      nodes[t].parent = new_node;
    }
    else {
      nodes[new_node].right = nodes[t].right;
      nodes[new_node].left = t;
      if (nodes[new_node].right != 0) {
        nodes[nodes[new_node].right].parent = new_node;
      }
      nodes[t].right = 0;
      nodes[t].parent = new_node;
    }

    UpdateSize(t);
    UpdateSize(new_node);
    root = new_node;
  }

  void Delete(int64_t key) {
    if (root == 0) {
      return;
    }
    int32_t t = Find(key);
    if (nodes[t].key != key) {
      return;
    }
    int32_t left_tree = nodes[t].left;
    int32_t right_tree = nodes[t].right;

    if (left_tree != 0) {
      nodes[left_tree].parent = 0;
    }
    if (right_tree != 0) {
      nodes[right_tree].parent = 0;
    }

    if (left_tree == 0) {
      root = right_tree;
    }
    else {
      root = left_tree;
      int32_t max_left = left_tree;
      while (nodes[max_left].right != 0) {
        max_left = nodes[max_left].right;
      }
      Splay(max_left);
      nodes[max_left].right = right_tree;
      if (right_tree != 0) {
        nodes[right_tree].parent = max_left;
      }
      UpdateSize(max_left);
    }
  }

  bool Exists(int64_t key) {
    if (root == 0) {
      return false;
    }
    int32_t t = Find(key);
    return nodes[t].key == key;
  }

  int64_t GetKth(int32_t k) {
    if (root == 0 || k < 0 || k >= nodes[root].size) {
      return -1;
    }

    int32_t cur = root;
    while (cur != 0) {
      int32_t left_size = 0;
      if (nodes[cur].left != 0) {
        left_size = nodes[nodes[cur].left].size;
      }
      if (left_size == k) {
        Splay(cur);
        return nodes[cur].key;
      }
      if (k < left_size) {
        cur = nodes[cur].left;
      }
      else {
        k = k - left_size - 1;
        cur = nodes[cur].right;
      }
    }
    return -1;
  }

  bool HasKth(int32_t k) {
    return (root != 0 && k >= 0 && k < nodes[root].size);
  }

  int32_t NextNode(int64_t key) {
    int32_t cur = root;
    int32_t succ = 0;
    int32_t last = 0;

    while (cur != 0) {
      last = cur;
      if (nodes[cur].key > key) {
        succ = cur;
        cur = nodes[cur].left;
      }
      else {
        cur = nodes[cur].right;
      }
    }

    if (succ != 0) {
      Splay(succ);
      return succ;
    }
    if (last != 0) {
      Splay(last);
    }
    return 0;
  }

  int32_t PrevNode(int64_t key) {
    int32_t cur = root;
    int32_t pred = 0;
    int32_t last = 0;

    while (cur != 0) {
      last = cur;
      if (nodes[cur].key < key) {
        pred = cur;
        cur = nodes[cur].right;
      }
      else {
        cur = nodes[cur].left;
      }
    }
    if (pred != 0) {
      Splay(pred);
      return pred;
    }
    if (last != 0) {
      Splay(last);
    }
    return 0;
  }

  int64_t GetKey(int32_t idx) {
    return nodes[idx].key;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  SplayTree tree;
  std::string operation;
  int64_t x;

  while (std::cin >> operation >> x) {
    if (operation == "insert") {
      tree.Insert(x);
    }
    else if (operation == "delete") {
      tree.Delete(x);
    }
    else if (operation == "exists") {
      if (tree.Exists(x)) {
        std::cout << "true\n";
      }
      else {
        std::cout << "false\n";
      }
    }
    else if (operation == "next") {
      int32_t result_node = tree.NextNode(x);
      if (result_node != 0) {
        std::cout << tree.GetKey(result_node) << '\n';
      }
      else {
        std::cout << "none\n";
      }
    }
    else if (operation == "prev") {
      int32_t result_node = tree.PrevNode(x);
      if (result_node != 0) {
        std::cout << tree.GetKey(result_node) << '\n';
      }
      else {
        std::cout << "none\n";
      }
    }
    else if (operation == "kth") {
      if (tree.HasKth((int32_t)x)) {
        std::cout << tree.GetKth((int32_t)x) << '\n';
      }
      else {
        std::cout << "none\n";
      }
    }
  }
  return 0;
}