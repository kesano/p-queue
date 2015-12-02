/*
 * File: pqueuepriv.h (array version)
 * ----------------------------------
 * This file contains the private section of the PriorityQueue class.
 */

/*
 * Implementation notes: PriorityQueue data structure
 * --------------------------------------------------
 * The array-based priority queue stores the elements in successive index
 * positions in an array.  What makes the priority queue structure more complex
 * is the need to avoid shifting elements as the queue expands and contracts. In
 * the array model, this goal is achieved by keeping track of both the head and
 * tail indices. The tail index increases by one each time an element is enqueued,
 * and the head index increases by one each time an element is dequeued. Each index
 * therefore marches toward the end of the allocated array and will eventually reach
 * the end. Rather than allocate new memory, this implementation lets each index wrap
 * around back to the beginning as if the ends of the array of elements were joined
 * to form a circle. This representation is called a ring buffer.
 *
 * The elements of the priority queue are stored in a dynamic array of the specified
 * element type. If the space in the array is ever exhausted, the implementation
 * doubles the array capacity. Note that the queue capacity is reached when there is
 * still one unused element in the array.  If the priority queue is allowed to fill
 * completely, the head and tail indices will have the same value, and the queue will
 * appear empty.
 */

private:

/* Type used for each heap entry */

   struct ValuePriorityPair {
      std::string value;
      double priority;
   };

/* Constants */

   static const int INITIAL_CAPACITY = 10;

/* Instance variables */

   ValuePriorityPair *array;
   int capacity;
   int head;
   int tail;

/* Private method prototypes */

   void expandCapacity();
   void deepCopy(const PriorityQueue & src);
