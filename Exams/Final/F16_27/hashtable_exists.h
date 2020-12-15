/*
 * hashtable_exists.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F16E2 Q27.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef HASHTABLE_EXISTS_H
#define HASHTABLE_EXISTS_H

#include <vector>

enum class Status { Empty, Deleted, Occupied };
struct HashTable {
  std::vector<int> buckets;
  std::vector<Status> status;
};

bool exists(const HashTable &tbl, int val);

#endif 
