// Project identifier: 19034C8F3B1196BF8E0C6E1C0F973D2FD550B88F

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the 'priority_queue' ADT implemented as a pairing heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure to
            // initialize it here.
            explicit Node(const TYPE &val)
                : elt{ val }, child{ nullptr }, sibling{ nullptr }, parent{ nullptr }
            {}

            // Description: Allows access to the element at that Node's position.
			// There are two versions, getElt() and a dereference operator, use
			// whichever one seems more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }
           
            // The following line allows you to access any private data members of this
            // Node class from within the PairingPQ class. (ie: myNode.elt is a legal
            // statement in PairingPQ's add_node() function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node* parent;
    }; // Node

    // Description: Construct an empty priority_queue with an optional comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, numNodes{ 0 }, root{ nullptr } {
        
    } // PairingPQ()


    // Description: Construct a priority_queue out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    // TODO: when you implement this function, uncomment the parameter names.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, numNodes{ 0 }, root{ nullptr } {
        while (start != end) {
            push(*start);
            ++start;
        }
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ& other) :
        BaseClass{ other.compare }, numNodes{ numNodes }, root{ nullptr }  {
       
        //If it's not already empty
        if (other.root) {
            dq.push_back(other.root);
            Node* cur = nullptr;

            while (!dq.empty()) {

                cur = dq.front();

                //Check for associates
                if (cur->sibling)
                    dq.push_back(cur->sibling);
                if (cur->child)
                    dq.push_back(cur->child);

                //Remove
                push(cur->getElt());
                dq.pop_front();
            }
        }
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    // TODO: when you implement this function, uncomment the parameter names.
    PairingPQ& operator=(const PairingPQ& rhs) {
        
        PairingPQ temp(rhs);
        std::swap(numNodes, temp.numNodes);
        std::swap(root, temp.root);
     
        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        
        //If it's not already empty
        if (root) {
            dq.push_back(root);
            Node* cur = nullptr;

            while (!dq.empty()) {

                cur = dq.front();

                //Check for associates
                if (cur->sibling)
                    dq.push_back(cur->sibling);
                if (cur->child)
                    dq.push_back(cur->child);

                //Remov
                --numNodes;
                delete cur;
                dq.pop_front();
            }
        }
        
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the priority_queue are out of order and
    //              'rebuilds' the priority_queue by fixing the priority_queue invariant.
    // Runtime: O(n)
    //Creates Deque and takes the and adds ptr to our current element to and this elements siblings to the deque
    //We then call meld on root and on the top of doeque and meld this with root and we keep breaking elements, 
    //Adding relations to the dequee, and then melding the top of the deque until DQ is empty
    virtual void updatePriorities() {
       
        //Manually do first one
        Node* cur = root;
        if (cur->child)
            dq.push_back(cur->child);
        cur->child = nullptr;
        
        while (!dq.empty()) {

            cur = dq.front();

            //Check for associates
            if (cur->sibling)
                dq.push_back(cur->sibling);
            if (cur->child)
                dq.push_back(cur->child);

            //Remove all associations
            cur->child = nullptr;
            cur->sibling = nullptr;
            cur->parent = nullptr;

            //Meld with root
            meld(root, cur);

            dq.pop_front();
        }
   
    } // updatePriorities()


    // Description: Add a new element to the priority_queue. This is almost done,
    //              in that you should implement push functionality in the addNode()
    //              function, and this function should call addNode().
    // Runtime: O(1)
    // TODO: when you implement this function, uncomment the parameter names.
    virtual void push(const TYPE & val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element from
    //              the priority_queue.
    // Note: We will not run tests on your code that would require it to pop an
    // element when the priority_queue is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: Amortized O(log(n))
    //
    virtual void pop() {
        Node* cur = root->child;
        
        //If there is more than one node
        if (cur)
        {
            //Loop through adding all elements in a row to deque
            while (cur) {
                dq.push_back(cur);
                cur = cur->sibling;
            }

            //Multipass meld until there is one element left in deque
            while (dq.size() > 1) {

                //Grab top element and braek connections
                cur = dq.front();
                cur->sibling = nullptr;
                cur->parent = nullptr;
                dq.pop_front();

                //Grab next elemnt and break connections
                dq.front()->sibling = nullptr;
                dq.front()->parent = nullptr;

                //Add new root node to back and pop
                dq.push_back(meld(cur, dq.front()));
                dq.pop_front();
            }

            //Remove current root and assign new root
            delete root;
            --numNodes;
            root = dq.front();
            dq.pop_front();
        }
        else {
            --numNodes;
            delete root;
            root = nullptr;
        }

    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the heap.  This should be a reference for speed.  It MUST be
    //              const because we cannot allow it to be modified, as that
    //              might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE & top() const {
        return root->elt;
    } // top()


    // Description: Get the number of elements in the priority_queue.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return numNodes;
    } // size()

    // Description: Return true if the priority_queue is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        return numNodes == 0;
    } // empty()


    // Description: Updates the priority of an element already in the priority_queue by
    //              replacing the element refered to by the Node with new_value.
    //              Must maintain priority_queue invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more extreme
    //               (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    // Given a vlue first thing you should do is change the appropriate value in the heap
    // 
    void updateElt(Node* /*node*/, const TYPE & /*new_value*/) {
        // TODO: Implement this function
    } // updateElt()


    // Description: Add a new element to the priority_queue. Returns a Node* corresponding
    //              to the newly added element.
    // Runtime: O(1)
    // TODO: when you implement this function, uncomment the parameter names.
    // NOTE: Whenever you create a node, and thus return a Node *, you must be sure to
    //       never move or copy/delete that node in the future, until it is eliminated
    //       by the user calling pop().  Remember this when you implement updateElt() and
    //       updatePriorities().
    Node* addNode(const TYPE & val) {
        Node* ptr = new Node{val};
        ++numNodes;
        if (root) {
            root = meld(ptr, root);
            return ptr;
        }
        else {
            return root = ptr;
        }
            
    } // addNode()


private:
    
    //Member Variables
    unsigned int numNodes = 0;
    Node* root = nullptr;
    std::deque<Node*> dq;
    //Function meld
    //Given two root pointers compares the two of them and makes the smaller one a child
    //of root and the root a parent of the smaller one
    //Does this by assigning a node that is smaller than root to be sibling of new node
    Node* meld(Node* a, Node* b) {
        
        //Check for Null (eventually delete)
        assert(a);
        assert(b);

        //If a is less than b
        if (this->compare(a->elt, b->elt)) {
            a->sibling = b->child;
            b->child = a;
            a->parent = b;
            
            return b;
        }

        //If a is greater than or equal to b
        else {
            b->sibling = a->child;
            a->child = b;
            b->parent = a;

            return a;
        }

        return nullptr;
    }
};

#endif // PAIRINGPQ_H
