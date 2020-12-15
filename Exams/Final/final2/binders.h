/*
 * binders.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 F20E2 Q25.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef BINDERS_H 
#define BINDERS_H

#include <vector>

int min_combine_cost(const std::vector<std::vector<int>> &binders);


/*
 * Implemented by instructor code. Student does not need to implement this function.
 */
int combine(const std::vector<int> &first, const std::vector<int> &second, std::vector<int> &output);

#endif
