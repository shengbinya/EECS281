/*
 * minmax_element.h
 * Univeristy of Michigan, Ann Arbor
 * EECS 281 std::minmax_element.
 * DO NOT SUBMIT TO GRADESCOPE.
 * If submitted, this file will be ignored.
 */
#ifndef MINMAX_ELEMENT_H
#define MINMAX_ELEMENT_H

#include <utility>

namespace eecs281 {

template <class ForwardIterator, class Compare>
std::pair<ForwardIterator, ForwardIterator> 
minmax_element(ForwardIterator first, ForwardIterator last, Compare comp);

}

#endif
