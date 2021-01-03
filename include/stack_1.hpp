// Copyright [2020] <Alyona Dorodnyaya>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <typename T>
class Stack {
 private:
  class Node {
    friend class Stack;

    const T value_;
    Node* next_ = nullptr;

    explicit Node(T value, Node* next) : value_(value), next_(next) {}
  };

  size_t size_;
  Node* first_;

 public:
  Stack() : size_(0), first_(nullptr) {}
  ~Stack();

  Stack(Stack& st) = default;
  Stack(Stack&& st) noexcept;

  Stack& operator=(Stack& st) = delete;
  Stack& operator=(Stack&& st) noexcept;

  size_t size();
  bool empty();
  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;

  template <typename... Args>
  void push_emplace(Args&&... value);

  // for main.cpp
  void print();
};

template <typename T>
void Stack<T>::push(const T& value) {
  static_assert(std::is_copy_constructible<T>::value,
                "It is not copy_constructible type");

  first_ = new Node{value, first_};
  size_++;
}

template <typename T>
void Stack<T>::push(T&& value) {
  static_assert(std::is_move_constructible<T>::value,
                "It is not move_constructible type");

  first_ = new Node{std::move(value), first_};
  size_++;
}

template <typename T>
void Stack<T>::pop() {
  Node* node = first_;
  if (node == nullptr) {
    throw std::out_of_range("This stack is empty");
  }

  // for size = 0: node->next_ = nullptr;
  first_ = node->next_;
  delete node;
  size_--;
}
template <typename T>
const T& Stack<T>::head() const {
  if (size_ != 0)
    return first_->value_;
  else
    throw std::out_of_range("This stack is empty");
}

template <typename T>
Stack<T>::Stack(Stack&& st) noexcept {
  first_ = nullptr;
  size_ = 0;
  std::swap(first_, st.first_);
  std::swap(size_, st.size_);
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& st) noexcept {
  if (&st != this) {
    first_ = nullptr;
    size_ = 0;
    std::swap(first_, st.first_);
    std::swap(size_, st.size_);
  }
  return *this;
}

template <typename T>
Stack<T>::~Stack() {
  Node* node = first_;
  while (node != nullptr) {
    Node* next = node->next_;
    delete node;
    node = next;
  }
  size_ = 0;
}

template <typename T>
template <typename... Args>
void Stack<T>::push_emplace(Args&&... value) {
  first_ = new Node{T{std::forward<Args>(value)...}, first_};
  size_++;
}

template <typename T>
size_t Stack<T>::size() {
  return size_;
}
template <typename T>
void Stack<T>::print() {
  std::cout << "Stack\nSize = " << size_ << std::endl;

  Node* node = first_;
  while (node != nullptr) {
    std::cout << node->value_ << ' ';
    node = node->next_;
  }
  std::cout << "\n\n";
}
template <typename T>
bool Stack<T>::empty() {
  return first_== nullptr;
}

#endif  // INCLUDE_HEADER_HPP_
