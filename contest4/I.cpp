#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

const int32_t cMaxN = 200005;
const int32_t cRandMult = 1664525;
const int32_t cRandAdd = 1013904223;
const int32_t cRandMod = 2147483647;
const int32_t cInitialRandSeed = 997;
const int32_t cMaxId = 200006;
const int32_t cMinId = -1;

struct Node {
  int64_t score;
  int64_t coins;
  int64_t lazy;
  int32_t id;
  int32_t priority;
  int32_t size;
  int32_t left;
  int32_t right;
};

Node nodes[cMaxN];
int64_t player_coins[cMaxN];
int64_t current_scores[cMaxN];
int32_t root = 0;
int32_t next_rand = cInitialRandSeed;
int32_t node_cnt = 0;

int32_t MyRand() {
  next_rand = (int32_t)((1LL * next_rand * cRandMult + cRandAdd) % cRandMod);
  return next_rand;
}

int64_t MyAbs(int64_t x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

int32_t NewNode(int64_t score, int32_t id) {
  node_cnt++;
  nodes[node_cnt].score = score;
  nodes[node_cnt].id = id;
  nodes[node_cnt].priority = MyRand();
  nodes[node_cnt].size = 1;
  nodes[node_cnt].left = 0;
  nodes[node_cnt].right = 0;
  nodes[node_cnt].coins = 0;
  nodes[node_cnt].lazy = 0;
  return node_cnt;
}

void UpdateSize(int32_t curr) {
  if (curr != 0) {
    nodes[curr].size =
      1 + nodes[nodes[curr].left].size + nodes[nodes[curr].right].size;
  }
}

void Push(int32_t curr) {
  if (curr != 0 && nodes[curr].lazy != 0) {
    int64_t lz = nodes[curr].lazy;
    nodes[curr].coins += lz;
    if (nodes[curr].left != 0) {
      nodes[nodes[curr].left].lazy += lz;
    }
    if (nodes[curr].right != 0) {
      nodes[nodes[curr].right].lazy += lz;
    }
    nodes[curr].lazy = 0;
  }
}

bool Less(int32_t curr, int64_t score, int32_t id) {
  if (nodes[curr].score < score) {
    return true;
  }
  if (nodes[curr].score == score) {
    if (nodes[curr].id < id) {
      return true;
    }
  }
  return false;
}

void Split(int32_t curr, int64_t score, int32_t id, int32_t& left_tree,
  int32_t& right_tree) {
  Push(curr);
  if (curr == 0) {
    left_tree = 0;
    right_tree = 0;
    return;
  }
  if (Less(curr, score, id) ||
    (nodes[curr].score == score && nodes[curr].id == id)) {
    Split(nodes[curr].right, score, id, nodes[curr].right, right_tree);
    left_tree = curr;
  }
  else {
    Split(nodes[curr].left, score, id, left_tree, nodes[curr].left);
    right_tree = curr;
  }
  UpdateSize(curr);
}

void Merge(int32_t& curr, int32_t left_tree, int32_t right_tree) {
  Push(left_tree);
  Push(right_tree);
  if (left_tree == 0) {
    curr = right_tree;
    return;
  }
  if (right_tree == 0) {
    curr = left_tree;
    return;
  }
  if (nodes[left_tree].priority > nodes[right_tree].priority) {
    Merge(nodes[left_tree].right, nodes[left_tree].right, right_tree);
    curr = left_tree;
  }
  else {
    Merge(nodes[right_tree].left, left_tree, nodes[right_tree].left);
    curr = right_tree;
  }
  UpdateSize(curr);
}

int32_t GetRank(int64_t score) {
  int32_t tree_less = 0;
  int32_t tree_greater = 0;
  Split(root, score, cMaxId, tree_less, tree_greater);
  int32_t rank = 0;
  if (tree_greater != 0) {
    rank = nodes[tree_greater].size;
  }
  Merge(root, tree_less, tree_greater);
  return rank;
}

void AddRangeCoins(int64_t min_score, int64_t max_score) {
  if (max_score <= min_score) {
    return;
  }
  int32_t t_less = 0;
  int32_t t_mid = 0;
  int32_t t_greater = 0;
  int32_t t_temp = 0;
  Split(root, min_score, cMinId, t_less, t_temp);
  Split(t_temp, max_score, cMinId, t_mid, t_greater);
  if (t_mid != 0) {
    nodes[t_mid].lazy += 1;
  }
  Merge(t_temp, t_mid, t_greater);
  Merge(root, t_less, t_temp);
}

void RemoveAndSaveCoins(int32_t id) {
  int32_t tree_less = 0;
  int32_t tree_target = 0;
  int32_t tree_greater = 0;
  int64_t score = current_scores[id];
  Split(root, score, id, tree_target, tree_greater);
  Split(tree_target, score, id - 1, tree_less, tree_target);
  if (tree_target != 0) {
    Push(tree_target);
    player_coins[id] += nodes[tree_target].coins;
  }
  Merge(root, tree_less, tree_greater);
}

void InsertNew(int32_t id, int64_t score) {
  int32_t tree_less = 0;
  int32_t tree_greater = 0;
  int32_t new_node = NewNode(score, id);
  Split(root, score, id, tree_less, tree_greater);
  Merge(root, tree_less, new_node);
  Merge(root, root, tree_greater);
}

void FinalizeCoins(int32_t curr) {
  if (curr == 0) {
    return;
  }
  Push(curr);
  player_coins[nodes[curr].id] += nodes[curr].coins;
  FinalizeCoins(nodes[curr].left);
  FinalizeCoins(nodes[curr].right);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int32_t n = 0;
  int32_t q = 0;
  if (!(std::cin >> n >> q)) {
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    current_scores[i] = 0;
    player_coins[i] = 0;
    InsertNew(i, 0);
  }
  for (int i = 0; i < q; i++) {
    int32_t id = 0;
    int64_t points = 0;
    std::cin >> id >> points;
    int64_t old_score = current_scores[id];
    int32_t old_rank = GetRank(old_score);
    RemoveAndSaveCoins(id);
    int64_t new_score = old_score + points;
    if (new_score > old_score) {
      AddRangeCoins(old_score, new_score);
    }
    else if (new_score < old_score) {
      AddRangeCoins(new_score, old_score);
    }
    current_scores[id] = new_score;
    InsertNew(id, new_score);
    int32_t new_rank = GetRank(new_score);
    player_coins[id] += MyAbs(old_rank - new_rank);
  }
  FinalizeCoins(root);
  for (int i = 1; i <= n; i++) {
    std::cout << player_coins[i] << '\n';
  }
  return 0;
}
