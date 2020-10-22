/*
 * set_difference.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 std::set_difference.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef SET_DIFFERENCE_H
#define SET_DIFFERENCE_H

namespace eecs281 {

template <class ForwardIterator1, class ForwardIterator2, class OutputIterator,
          class Compare>
OutputIterator set_difference(ForwardIterator1 first1, ForwardIterator1 last1,
                              ForwardIterator2 first2, ForwardIterator2 last2,
                              OutputIterator result, Compare comp);

}

#endif
