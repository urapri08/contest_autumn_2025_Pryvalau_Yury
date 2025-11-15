#include <iostream>
#include <string>
#include<stdint.h>

struct Stack {
  Stack* back;
  Stack* next;
  int32_t val;
  Stack(Stack* b, Stack* d, int32_t c) : back(b), next(d), val(c) {}
};

Stack* Enqueue(Stack* st, int32_t t) {
  Stack* now = new Stack(nullptr, nullptr, t);
  if (st == nullptr) {
    return now;
  }
  now->next = st;
  st->back = now;
  return now;
}

Stack* Dequeue(Stack* st) {
  if (st == nullptr) {
    return nullptr;
  }
  std::cout << st->val << "\n";
  if (st->back == nullptr) {
    delete st;
    return nullptr;
  }
  Stack* now = st->back;
  now->next = nullptr;
  delete st;
  return now;
}

Stack* Mid(Stack* st, int32_t t) {
  Stack* now = new Stack(nullptr, nullptr, t);
  if (st == nullptr) {
    return now;
  }
  if (st->back != nullptr) {
    st->back->next = now;
    now->back = st->back;
  }
  now->next = st;
  st->back = now;
  return now;
}

void FreeStack(Stack* st) {
  while (st != nullptr) {
    Stack* temp = st;
    st = st->back;
    delete temp;
  }
}

int main() {
  int32_t size = 0;
  int32_t get;
  int32_t length = 0;
  std::string com;
  Stack* head = nullptr;
  Stack* tail = nullptr;
  Stack* mid = nullptr;
  std::cin >> size;
  for (int32_t i = 0; i < size; i++) {
    std::cin >> com;
    if (com == "+") {
      std::cin >> get;
      tail = Enqueue(tail, get);
      if (head == nullptr) {
        head = tail;
        mid = head;
      }
      else if (length % 2 == 0 && mid->back != nullptr) {
        mid = mid->back;
      }
      length++;
    }
    else if (com == "-") {
      if (head == mid && head != nullptr && head->back != nullptr) {
        mid = head->back;
      }
      head = Dequeue(head);
      if (head == nullptr) {
        tail = nullptr;
        mid = nullptr;
      }
      else if (length % 2 == 0 && mid != nullptr && mid->back != nullptr) {
        mid = mid->back;
      }
      length--;
    }
    else if (com == "*") {
      std::cin >> get;
      if (head == nullptr) {
        head = new Stack(nullptr, nullptr, get);
        tail = head;
        mid = head;
        length = 1;
      }
      else {
        Stack* nmid = Mid(mid, get);
        if (mid == tail) {
          tail = nmid;
        }
        if (length % 2 == 0) {
          mid = nmid;
        }
        length++;
      }
    }
  }
  FreeStack(head);
  return 0;
}



