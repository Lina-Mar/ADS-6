// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

struct SYM {
  char ch;
  int prior;
};

template <typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& data, Node* next = nullptr)
        : data(data), next(next) {}
  };
    Node* head;
    Node* tail;
    int size;

 public:
  TPQueue() : head(nullptr), tail(nullptr), size(0) {}
  ~TPQueue();
    void push(const T& item);
    T pop();
    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }
};

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
template <typename T>
void TPQueue<T>::push(const T& item) {
    Node* newNode = new Node(item);
    if (head == nullptr || item.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
        if (tail == nullptr) {
          tail = newNode;
        }
        size++;
        return;
    }
    Node* current = head;
    while (current->next != nullptr 
      && current->next->data.prior >= item.prior) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;

    if (newNode->next == nullptr) {
      tail = newNode;
    }
    size++;
}

template <typename T>
T TPQueue<T>::pop() {
    if (isEmpty()) {
      throw "Queue is empty";
    }
    Node* temp = head;
    T data = temp->data;
    head = head->next;
    if (head == nullptr) {
      tail = nullptr;
    }
    delete temp;
    size--;
    return data;
}

#endif  // INCLUDE_TPQUEUE_H_
