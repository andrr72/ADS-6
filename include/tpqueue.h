// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& d) : data(d), next(nullptr) {}
  };
  Node* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(const T& item) {
    Node* newNode = new Node(item);
    if (!head || head->data.prior < item.prior) {
      newNode->next = head;
      head = newNode;
    } else {
      Node* current = head;
      while (current->next && current->next->data.prior >= item.prior) {
        current = current->next;
      }
      newNode->next = current->next;
      current->next = newNode;
    }
  }

  T pop() {
    if (!head) throw std::runtime_error("Queue is empty");
    Node* temp = head;
    T data = temp->data;
    head = head->next;
    delete temp;
    return data;
  }

  T& top() {
    if (!head) throw std::runtime_error("Queue is empty");
    return head->data;
  }

  bool empty() const {
    return head == nullptr;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
