// Project identifier: 19034C8F3B1196BF8E0C6E1C0F973D2FD550B88F

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"

// A specialized version of the 'heap' ADT implemented as a binary heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty heap with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
    } // BinaryPQ


    // Description: Construct a heap out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    // TODO: when you implement this function, uncomment the parameter names.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {

        while (start != end) {
            data.push_back(*start);
            start++;
        }
        
        //Update Ordering
        updatePriorities();

    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automaticslly.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of order and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        for (int i = int(size()); i > 0; i--) {
            fixDown(i);
        }
    } // updatePriorities()


    // Description: Add a new element to the heap.
    // Runtime: O(log(n))
    // TODO: when you implement this function, uncomment the parameter names.
    virtual void push(const TYPE & val) {
        data.push_back(val);
        fixUp();
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element from
    //              the heap.
    // Note: We will not run tests on your code that would require it to pop an
    // element when the heap is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop() {
        int i = int(size());
        getElement(1) = getElement(i--);
        data.pop_back();
        fixDown(1);
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the heap.  This should be a reference for speed.  It MUST be
    //              const because we cannot allow it to be modified, as that
    //              might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE & top() const {
        return data.at(0);
    } // top()


    // Description: Get the number of elements in the heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return data.size();
    } // size()


    // Description: Return true if the heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        return data.empty();
    } // empty()


private:
    // Note: This vector *must* be used your heap implementation.
    std::vector<TYPE> data;

    void fixUp() {
        
        int k = int(size());

        //While K is not root and value at k is greater than it's parent at k/2
        while (k > 1 && this->compare(getElement(k / 2), getElement(k))) {
            
            //Swap K up
            std::swap(getElement(k), getElement(k / 2));
            
            //Set equal to new swapped index
            k /= 2;
        }
    }
    //Huge change
    void fixDown(unsigned int k) {

        //While we have not gone past the bottom of the heap
        while (2 * k <= size()) {

            unsigned int j = 2 * k; //Check index of the left child

            //If the left child is smaller than the right child set j to right child
            //so you swap with the larger of the two, make sure not going out of bounds
            if (j < size() && this->compare(getElement(j), getElement(j + 1))) ++j;

            //If our value is larger than or equal to value below us heap restored
            if ( !this->compare(getElement(k), getElement(j)) ) break;

            //Swap if we've made it this far and determined what to swap with
            std::swap(getElement(k), getElement(j));

            k = j;
        }
        
    }

    TYPE& getElement(std::size_t i) {
        return data[i - 1];
    }

}; // BinaryPQ


#endif // BINARYPQ_H
