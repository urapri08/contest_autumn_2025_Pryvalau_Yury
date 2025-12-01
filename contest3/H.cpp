#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

const int cReservingMultiplier = 4;

struct Event {
  long long x;
  long long y1;
  long long y2;
  int type;
};

bool CompareEvents(const Event& a, const Event& b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return a.type > b.type;
}

class SegmentTree {
private:
  std::vector<int> cnt_;
  std::vector<long long> len_;
  std::vector<long long> y_;
  void Build(int v, int l, int r) {
    if (r - l == 1) {
      len_[v] = 0;
      return;
    }
    int m = (l + r) / 2;
    Build(2 * v + 1, l, m);
    Build(2 * v + 2, m, r);
    len_[v] = len_[2 * v + 1] + len_[2 * v + 2];
  }

public:
  SegmentTree(const std::vector<long long>& coord)
    : y_(coord),
    cnt_(cReservingMultiplier* (coord.size() - 1)),
    len_(cReservingMultiplier* (coord.size() - 1)) {
    Build(0, 0, coord.size() - 1);
  }
  void Update(int v, int l, int r, int ql, int qr, int val) {
    if (ql >= r || qr <= l) {
      return;
    }
    if (ql <= l && r <= qr) {
      cnt_[v] += val;
    }
    else {
      int m = (l + r) / 2;
      Update(2 * v + 1, l, m, ql, qr, val);
      Update(2 * v + 2, m, r, ql, qr, val);
    }
    if (cnt_[v] > 0) {
      len_[v] = y_[r] - y_[l];
    }
    else {
      if (r - l == 1) {
        len_[v] = 0;
      }
      else {
        len_[v] = len_[2 * v + 1] + len_[2 * v + 2];
      }
    }
  }
  long long GetLen() { return len_[0]; }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<Event> ev;
  std::vector<long long> ys;
  for (int i = 0; i < n; i++) {
    long long x1;
    long long y1;
    long long x2;
    long long y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    ev.push_back({ x1, y1, y2, 1 });
    ev.push_back({ x2, y1, y2, -1 });
    ys.push_back(y1);
    ys.push_back(y2);
  }
  std::sort(ys.begin(), ys.end());
  ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
  std::map<long long, int> comp;
  for (int i = 0; i < (int)ys.size(); i++) {
    comp[ys[i]] = i;
  }
  std::sort(ev.begin(), ev.end(), CompareEvents);
  SegmentTree st(ys);
  long long ans = 0;
  long long prev = ev[0].x;
  for (const Event& e : ev) {
    if (e.x != prev) {
      ans += st.GetLen() * (e.x - prev);
      prev = e.x;
    }
    int l = comp[e.y1];
    int r = comp[e.y2];
    st.Update(0, 0, ys.size() - 1, l, r, e.type);
  }
  std::cout << ans << '\n';
  return 0;
}