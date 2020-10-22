/*
 * linearize.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 W18E1 Q27.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef LINEARIZE_H 
#define LINEARIZE_H

struct Node {
  int val;
  Node* left;
  Node* right;
};

void linearize(Node* binary_heap);

#endif
