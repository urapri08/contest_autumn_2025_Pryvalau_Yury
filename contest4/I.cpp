#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

const int32_t cMaxN = 200'005;
const int32_t cMaxId = 200'006;
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

  Node()
    : score(0), coins(0), lazy(0), id(0), priority(0), size(0), left(0), right(0) {
  }

  Node(int64_t score_val, int32_t id_val, int32_t priority_val)
    : score(score_val), coins(0), lazy(0), id(id_val),
    priority(priority_val), size(1), left(0), right(0) {
  }
};

class TreapSolver {
private:
  std::vector<Node> nodes;
  int32_t root;
  std::mt19937 rng;

  int64_t MyAbs(int64_t x) {
    return (x < 0) ? -x : x;
  }

  int32_t NewNode(int64_t score, int32_t id) {
    int32_t priority = static_cast<int32_t>(rng());
    nodes.emplace_back(score, id, priority);
    return static_cast<int32_t>(nodes.size()) - 1;
  }

  void UpdateSize(int32_t curr) {
    if (curr != 0) {
      nodes[curr].size = 1 + nodes[nodes[curr].left].size + nodes[nodes[curr].right].size;
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

  void Split(int32_t curr, int64_t score, int32_t id, int32_t& left_tree, int32_t& right_tree) {
    Push(curr);
    if (curr == 0) {
      left_tree = 0;
      right_tree = 0;
      return;
    }

    bool go_right = Less(curr, score, id) || (nodes[curr].score == score && nodes[curr].id == id);

    if (go_right) {
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

  void CollectCoinsRecursive(int32_t curr, std::vector<int64_t>& player_coins) {
    if (curr == 0) {
      return;
    }
    Push(curr);
    if (nodes[curr].id > 0 && nodes[curr].id < (int32_t)player_coins.size()) {
      player_coins[nodes[curr].id] += nodes[curr].coins;
    }
    CollectCoinsRecursive(nodes[curr].left, player_coins);
    CollectCoinsRecursive(nodes[curr].right, player_coins);
  }

public:
  TreapSolver() : root(0), rng(997) {
    nodes.reserve(cMaxN);
    nodes.push_back(Node());
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

  void RemoveAndSaveCoins(int32_t id, int64_t current_score, std::vector<int64_t>& player_coins) {
    int32_t tree_less = 0;
    int32_t tree_target = 0;
    int32_t tree_greater = 0;

    Split(root, current_score, id, tree_target, tree_greater);
    Split(tree_target, current_score, id - 1, tree_less, tree_target);

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

  void FinalizeCoins(std::vector<int64_t>& player_coins) {
    CollectCoinsRecursive(root, player_coins);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int32_t n = 0;
  int32_t q = 0;
  if (!(std::cin >> n >> q)) {
    return 0;
  }

  std::vector<int64_t> current_scores(n + 1, 0);
  std::vector<int64_t> player_coins(n + 1, 0);

  TreapSolver treap;

  for (int i = 1; i <= n; i++) {
    treap.InsertNew(i, 0);
  }

  for (int i = 0; i < q; i++) {
    int32_t id = 0;
    int64_t points = 0;
    std::cin >> id >> points;

    int64_t old_score = current_scores[id];
    int32_t old_rank = treap.GetRank(old_score);

    treap.RemoveAndSaveCoins(id, old_score, player_coins);

    int64_t new_score = old_score + points;
    if (new_score > old_score) {
      treap.AddRangeCoins(old_score, new_score);
    }
    else if (new_score < old_score) {
      treap.AddRangeCoins(new_score, old_score);
    }

    current_scores[id] = new_score;
    treap.InsertNew(id, new_score);

    int32_t new_rank = treap.GetRank(new_score);
    int64_t rank_diff = (old_rank > new_rank) ? (old_rank - new_rank) : (new_rank - old_rank);
    player_coins[id] += rank_diff;
  }

  treap.FinalizeCoins(player_coins);

  for (int i = 1; i <= n; i++) {
    std::cout << player_coins[i] << '\n';
  }

  return 0;
}
