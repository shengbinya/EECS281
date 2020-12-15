/*
 * range_queries.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 W19E2 Q26.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef RANGE_QUERIES_H
#define RANGE_QUERIES_H

#include <vector>

struct Query {
  unsigned int id, start, end;
};

void range_queries(const std::vector<unsigned int>& data,
                   const std::vector<Query>& queries);

#endif
