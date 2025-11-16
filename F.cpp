#include <algorithm>
#include <iostream>
#include <string>
#include<stdint.h>

struct Stack {
  Stack* back = nullptr;
  int32_t num;
  int32_t min;
  Stack(Stack* b, int32_t c, int32_t u) : back(b), num(c), min(u) {}
};

Stack* Push(Stack* st, int32_t get) {
  int32_t new_min;
  if (st == nullptr) {
    new_min = get;
  }
  else {
    new_min = std::min(st->min, get);
  }
  Stack* now = new Stack(st, get, new_min);
  return now;
}

Stack* Pop(Stack* st) {
  if (st == nullptr) {
    return nullptr;
  }
  Stack* now = st->back;
  delete st;
  return now;
}

void FreeStack(Stack* head) {
  while (head != nullptr) {
    Stack* now = head;
    head = head->back;
    delete now;
  }
}

Stack* Shift(Stack* st, Stack* que) {
  Stack* now = que;
  while (st != nullptr) {
    now = Push(now, st->num);
    st = Pop(st);
  }
  return now;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int32_t size = 0;
  int32_t get;
  int32_t length;
  std::cin >> length;
  std::string com;
  Stack* head_st = nullptr;
  Stack* head_que = nullptr;
  for (int32_t i = 0; i < length; i++) {
    std::cin >> com;
    if (com == "enqueue") {
      std::cin >> get;
      head_st = Push(head_st, get);
      std::cout << "ok"
        << "\n";
      size++;
    }
    else if (com == "dequeue") {
      if (head_que != nullptr) {
        std::cout << head_que->num << "\n";
        head_que = Pop(head_que);
        size--;
      }
      else if (head_st != nullptr) {
        head_que = Shift(head_st, head_que);
        head_st = nullptr;
        std::cout << head_que->num << "\n";
        head_que = Pop(head_que);
        size--;
      }
      else {
        std::cout << "error"
          << "\n";
      }
    }
    else if (com == "front") {
      if (head_que != nullptr) {
        std::cout << head_que->num << "\n";
      }
      else if (head_st != nullptr) {
        head_que = Shift(head_st, head_que);
        head_st = nullptr;
        std::cout << head_que->num << "\n";
      }
      else {
        std::cout << "error"
          << "\n";
      }
    }
    else if (com == "size") {
      std::cout << size << "\n";
    }
    else if (com == "clear") {
      FreeStack(head_que);
      head_que = nullptr;
      FreeStack(head_st);
      head_st = nullptr;
      size = 0;
      std::cout << "ok"
        << "\n";
    }
    else if (com == "min") {
      if (size == 0) {
        std::cout << "error"
          << "\n";
      }
      else if (head_que != nullptr && head_st != nullptr) {
        std::cout << std::min(head_que->min, head_st->min) << "\n";
      }
      else if (head_que != nullptr) {
        std::cout << head_que->min << "\n";
      }
      else {
        std::cout << head_st->min << "\n";
      }
    }
  }
  FreeStack(head_que);
  FreeStack(head_st);
  return 0;
}



