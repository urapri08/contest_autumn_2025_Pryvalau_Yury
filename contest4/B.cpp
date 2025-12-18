#include <cstdint>
#include <iostream>
#include <string>

const int32_t cMaxNodes = 300005;

struct Node {
  int64_t key;
  int32_t left;
  int32_t right;
  int32_t parent;
  int32_t size;
};

Node nodes[cMaxNodes];
int32_t node_count = 0;
int32_t root = 0;

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
  int32_t p;
  int32_t g;
  int32_t child;
  p = nodes[t].parent;
  g = nodes[p].parent;

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
  int32_t p;
  int32_t g;
  while (nodes[t].parent != 0) {
    p = nodes[t].parent;
    g = nodes[p].parent;
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
  int32_t cur;
  int32_t last;
  cur = root;
  last = 0;
  if (root == 0) {
    return 0;
  }
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

void Insert(int64_t key) {
  int32_t t;
  int32_t new_node;

  if (root == 0) {
    node_count++;
    new_node = node_count;
    nodes[new_node].key = key;
    nodes[new_node].left = 0;
    nodes[new_node].right = 0;
    nodes[new_node].parent = 0;
    nodes[new_node].size = 1;
    root = new_node;
    return;
  }

  t = Find(key);
  if (nodes[t].key == key) {
    return;
  }

  node_count++;
  new_node = node_count;
  nodes[new_node].key = key;
  nodes[new_node].parent = 0;
  nodes[new_node].size = 1;

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
  int32_t t;
  int32_t left_tree;
  int32_t right_tree;
  int32_t max_left;
  if (root == 0) {
    return;
  }
  t = Find(key);
  if (nodes[t].key != key) {
    return;
  }
  left_tree = nodes[t].left;
  right_tree = nodes[t].right;
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
    max_left = left_tree;
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
  int32_t t;
  if (root == 0) {
    return false;
  }
  t = Find(key);
  return nodes[t].key == key;
}

int32_t GetKth(int32_t k) {
  int32_t cur;
  int32_t left_size;
  if (root == 0 || k < 0 || k >= nodes[root].size) {
    return 0;
  }
  cur = root;
  while (cur != 0) {
    left_size = 0;
    if (nodes[cur].left != 0) {
      left_size = nodes[nodes[cur].left].size;
    }
    if (left_size == k) {
      Splay(cur);
      return cur;
    }
    if (k < left_size) {
      cur = nodes[cur].left;
    }
    else {
      k = k - left_size - 1;
      cur = nodes[cur].right;
    }
  }
  return 0;
}

int32_t Next(int64_t key) {
  int32_t cur;
  int32_t succ;
  int32_t last;
  cur = root;
  succ = 0;
  last = 0;
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

int32_t Prev(int64_t key) {
  int32_t cur;
  int32_t pred;
  int32_t last;
  cur = root;
  pred = 0;
  last = 0;
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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string operation;
  int64_t x;
  int32_t result_node;
  while (std::cin >> operation >> x) {
    if (operation == "insert") {
      Insert(x);
    }
    else if (operation == "delete") {
      Delete(x);
    }
    else if (operation == "exists") {
      if (Exists(x)) {
        std::cout << "true\n";
      }
      else {
        std::cout << "false\n";
      }
    }
    else if (operation == "next") {
      result_node = Next(x);
      if (result_node != 0) {
        std::cout << nodes[result_node].key << '\n';
      }
      else {
        std::cout << "none\n";
      }
    }
    else if (operation == "prev") {
      result_node = Prev(x);
      if (result_node != 0) {
        std::cout << nodes[result_node].key << '\n';
      }
      else {
        std::cout << "none\n";
      }
    }
    else if (operation == "kth") {
      result_node = GetKth((int32_t)x);
      if (result_node != 0) {
        std::cout << nodes[result_node].key << '\n';
      }
      else {
        std::cout << "none\n";
      }
    }
  }
  return 0;
}