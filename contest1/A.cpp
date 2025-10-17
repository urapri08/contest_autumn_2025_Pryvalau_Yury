#include <iostream>
#include <vector>
#include<>

struct Seg {
  int start;
  int end;
  Seg(int s, int e) : start(s), end(e) {}
};

void MergeSegments(std::vector<Seg>& segs, int left, int mid, int right) {
  int left_size = mid - left + 1;
  int right_size = right - mid;
  std::vector<Seg> left_part(left_size, Seg(0, 0));
  std::vector<Seg> right_part(right_size, Seg(0, 0));
  for (int i = 0; i < left_size; i++) {
    left_part[i] = segs[left + i];
  }
  for (int j = 0; j < right_size; j++) {
    right_part[j] = segs[mid + 1 + j];
  }
  int i = 0;
  int j = 0;
  int k = left;
  while (i < left_size && j < right_size) {
    if (left_part[i].start <= right_part[j].start) {
      segs[k] = left_part[i];
      i++;
    }
    else {
      segs[k] = right_part[j];
      j++;
    }
    k++;
  }
  while (i < left_size) {
    segs[k] = left_part[i];
    i++;
    k++;
  }
  while (j < right_size) {
    segs[k] = right_part[j];
    j++;
    k++;
  }
}

void SortSegments(std::vector<Seg>& segs, int left, int right) {
  if (left >= right) {
    return;
  }
  int mid = left + (right - left) / 2;
  SortSegments(segs, left, mid);
  SortSegments(segs, mid + 1, right);
  MergeSegments(segs, left, mid, right);
}

std::vector<Seg> MergeOverlapping(std::vector<Seg>& segs) {
  if (segs.empty()) {
    return {};
  }
  std::vector<Seg> result;
  Seg current = segs[0];
  for (int i = 1; i < (int)segs.size(); i++) {
    if (segs[i].start <= current.end) {
      if (segs[i].end > current.end) {
        current.end = segs[i].end;
      }
    }
    else {
      result.push_back(current);
      current = segs[i];
    }
  }
  result.push_back(current);
  return result;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<Seg> segs;
  for (int i = 0; i < n; i++) {
    int start;
    int end;
    std::cin >> start >> end;
    segs.push_back(Seg(start, end));
  }
  if (n > 0) {
    SortSegments(segs, 0, segs.size() - 1);
  }
  std::vector<Seg> answer = MergeOverlapping(segs);
  std::cout << answer.size() << std::endl;
  for (int i = 0; i < (int)answer.size(); i++) {
    std::cout << answer[i].start << " " << answer[i].end << std::endl;
  }
  return 0;
}