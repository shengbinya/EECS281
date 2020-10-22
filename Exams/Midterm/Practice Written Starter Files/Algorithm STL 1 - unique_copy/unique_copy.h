/*
 * unique_copy.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 std::unique_copy.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef UNIQUE_COPY_H
#define UNIQUE_COPY_H

namespace eecs281 {

template <class ForwardIterator, class OutputIterator>
OutputIterator unique_copy(ForwardIterator first, ForwardIterator last,
                           OutputIterator result);

}

#endif
