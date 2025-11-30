#include <iostream>
#include <vector>

const int cMaxNodes = 4000000;

struct Node {
  int left = 0, right = 0, count = 0;
};

std::vector<Node> tree;
std::vector<int> roots, perm;

int BuildEmpty(int l, int r) {
  int id = tree.size();
  tree.push_back(Node());
  if (l != r) {
    int mid = (l + r) / 2;
    tree[id].left = BuildEmpty(l, mid);
    tree[id].right = BuildEmpty(mid + 1, r);
  }
  return id;
}

int Update(int prev_root, int l, int r, int pos) {
  int id = tree.size();
  tree.push_back(tree[prev_root]);
  tree[id].count++;
  if (l != r) {
    int mid = (l + r) / 2;
    if (pos <= mid) {
      tree[id].left = Update(tree[prev_root].left, l, mid, pos);
    }
    else {
      tree[id].right = Update(tree[prev_root].right, mid + 1, r, pos);
    }
  }
  return id;
}

int Query(int node, int l, int r, int ql, int qr) {
  if (ql > r || qr < l) {
    return 0;
  }
  if (ql <= l && r <= qr) {
    return tree[node].count;
  }
  int mid = (l + r) / 2;
  return Query(tree[node].left, l, mid, ql, qr) +
    Query(tree[node].right, mid + 1, r, ql, qr);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  int q;
  std::cin >> n >> q;
  perm.resize(n);
  for (int i = 0; i < n; i++) {
    std::cin >> perm[i];
    perm[i]--;
  }
  tree.reserve(cMaxNodes);
  roots.resize(n + 1);
  roots[0] = BuildEmpty(0, n - 1);
  for (int i = 0; i < n; i++) {
    roots[i + 1] = Update(roots[i], 0, n - 1, perm[i]);
  }
  for (int i = 0; i < q; i++) {
    int l;
    int r;
    int x;
    int y;
    std::cin >> l >> r >> x >> y;
    l--;
    r--;
    x--;
    y--;
    std::cout << (Query(roots[r + 1], 0, n - 1, x, y) -
      Query(roots[l], 0, n - 1, x, y))
      << '\n';
  }
  return 0;
}