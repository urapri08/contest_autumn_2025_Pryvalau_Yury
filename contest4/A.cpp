#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

const int32_t cModValue = 1000000000;

struct TreeVale {
  int64_t key;
  int32_t height;
  TreeVale* left;
  TreeVale* right;

  TreeVale(int64_t k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
  TreeVale* root_;
  static int32_t GetHeight(TreeVale* node) {
    if (node == nullptr) {
      return 0;
    }
    return node->height;
  }
  static int32_t FixBalance(TreeVale* node) {
    if (node == nullptr) {
      return 0;
    }
    return GetHeight(node->left) - GetHeight(node->right);
  }
  static void FixHeight(TreeVale* node) {
    if (node == nullptr) {
      return;
    }
    int32_t left_height = GetHeight(node->left);
    int32_t right_height = GetHeight(node->right);
    if (left_height > right_height) {
      node->height = left_height + 1;
    }
    else {
      node->height = right_height + 1;
    }
  }
  static TreeVale* RotateRight(TreeVale* y) {
    if (y == nullptr) {
      return nullptr;
    }
    TreeVale* x = y->left;
    if (x == nullptr) {
      return y;
    }
    TreeVale* t2 = x->right;
    x->right = y;
    y->left = t2;
    FixHeight(y);
    FixHeight(x);
    return x;
  }
  static TreeVale* RotateLeft(TreeVale* x) {
    if (x == nullptr) {
      return nullptr;
    }
    TreeVale* y = x->right;
    if (y == nullptr) {
      return x;
    }
    TreeVale* t2 = y->left;
    y->left = x;
    x->right = t2;
    FixHeight(x);
    FixHeight(y);
    return y;
  }
  static TreeVale* BalanceNode(TreeVale* node) {
    if (node == nullptr) {
      return node;
    }
    FixHeight(node);
    int32_t balance = FixBalance(node);
    if (balance > 1) {
      if (FixBalance(node->left) < 0) {
        node->left = RotateLeft(node->left);
      }
      return RotateRight(node);
    }
    if (balance < -1) {
      if (FixBalance(node->right) > 0) {
        node->right = RotateRight(node->right);
      }
      return RotateLeft(node);
    }
    return node;
  }
  static TreeVale* InsertNew(TreeVale* node, int64_t key) {
    if (node == nullptr) {
      return new TreeVale(key);
    }
    if (key < node->key) {
      node->left = InsertNew(node->left, key);
    }
    else if (key > node->key) {
      node->right = InsertNew(node->right, key);
    }
    else {
      return node;
    }
    return BalanceNode(node);
  }
  static int64_t FindLowerBound(TreeVale* node, int64_t key) {
    if (node == nullptr) {
      return -1;
    }
    if (node->key < key) {
      return FindLowerBound(node->right, key);
    }
    int64_t left_res = FindLowerBound(node->left, key);
    if (left_res != -1) {
      return left_res;
    }
    return node->key;
  }
  static void ClearTree(TreeVale* node) {
    if (node == nullptr) {
      return;
    }
    ClearTree(node->left);
    ClearTree(node->right);
    delete node;
  }

public:
  AVLTree() : root_(nullptr) {}
  ~AVLTree() { ClearTree(root_); }
  void Insert(int64_t key) { root_ = InsertNew(root_, key); }
  int64_t LowerBound(int64_t key) { return FindLowerBound(root_, key); }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int32_t query_count;
  if (std::cin >> query_count) {
    AVLTree avl_tree;
    int64_t last = 0;
    bool prev_q = false;
    for (int i = 0; i < query_count; i++) {
      char operation;
      int64_t value;
      std::cin >> operation >> value;
      if (operation == '+') {
        if (prev_q) {
          value = (value + last) % cModValue;
          if (value == 0) {
            value = cModValue;
          }
        }
        avl_tree.Insert(value);
        prev_q = false;
      }
      else {
        last = avl_tree.LowerBound(value);
        std::cout << last << "\n";
        prev_q = true;
      }
    }
  }
  return 0;
}