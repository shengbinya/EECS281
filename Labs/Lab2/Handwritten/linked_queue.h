/*
 * linked_queue.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 Lab 2 Written.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stddef.h>

template <typename T>
struct Node {
  T value;
  Node* next;
};

template <typename T>
class LinkedQueue {
 private:
  Node<T>* head = nullptr;
  Node<T>* tail = nullptr;
  size_t count = 0;

 public:
  T front() const;
  void pop();
  void push(T x);
  size_t size() const { return count; }
  bool empty() const { return count == 0; }
  ~LinkedQueue();
};

#endif
