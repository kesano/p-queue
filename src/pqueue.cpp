/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

/*
 * Implementation notes: Constructor
 * ---------------------------------
 * Allocates an empty array in the heap and initializes the priority queue fields to their
 * default values.
 */

PriorityQueue::PriorityQueue() {
    capacity = INITIAL_CAPACITY;
    array = new ValuePriorityPair[capacity];
    head = tail = 0;
}

/*
 * Implementation notes: Destructor
 * --------------------------------
 * Frees all heap memory previously associated with the priority queue, which is simply
 * the dynamic array of elements.
 */

PriorityQueue::~PriorityQueue() {
    delete[] array;
}

int PriorityQueue::size() const {
    return (tail + capacity - head) % capacity;
}

bool PriorityQueue::isEmpty() {
    return head == tail;
}

void PriorityQueue::clear() {
    head = tail = 0;
}

/*
 * Implementation notes: enqueue
 * -----------------------------
 * Before enqueueing the new element in its appropriate position in the priority queue, this
 * method must first check whether there is enough room for the element and expand the array
 * storage if necessary. Elements lower in priority are shifted one place to the right to make
 * space for the new element, if necessary, otherwise the new element is appended to the end
 * of the queue. Because it is otherwise impossible to differentiate the case when a priority
 * queue is empty from when it is completely full, this implementation expands the queue when
 * the size is one less than the capacity.
 */

void PriorityQueue::enqueue(string value, double priority) {
    if (size() == capacity - 1) expandCapacity();
    ValuePriorityPair p;
    p.value = value;
    p.priority = priority;
    if (!isEmpty()) {
        for (int i = 0; i < size(); i++) {
            if (p.priority < array[(head + i) % capacity].priority) {
                ValuePriorityPair tmp1 = array[(head + i) % capacity];
                array[(head + i) % capacity] = p;
                for (int j = i; j < size(); j++) {
                    ValuePriorityPair tmp2 = array[(head + j + 1) % capacity];
                    array[(head + j + 1) % capacity] = tmp1;
                    tmp1 = tmp2;
                }
                break;
            }
            if (i == size() - 1 && p.priority >= array[(head + i) % capacity].priority) {
                array[(head + i + 1) % capacity] = p;
                break;
            }
        }
    } else {
        array[0] = p;
    }
    tail = (tail + 1) % capacity;
}

/*
 * Implementation notes: dequeue
 * -----------------------------
 * Due to its ring buffer representation, dequeueing a value from the priority queue
 * is as straightforward as returning the value at the head of the queue and updating
 * head to be the position of the next value in the queue. Thus, this implementation
 * runs in constant time.
 */

string PriorityQueue::dequeue() {
    if (isEmpty()) error("dequeue: Attempting to dequeue an empty priority queue");
    string value = array[head].value;
    head = (head + 1) % capacity;
    return value;
}

string PriorityQueue::peek() {
    if (isEmpty()) error("peek: Attempting to peek an empty priority queue");
    return array[head].value;
}

double PriorityQueue::peekPriority() {
    if (isEmpty()) error("peekPriority: Attempting to peek an empty priority queue");
    return array[head].priority;
}

/*
 * Implementation notes: copy constructor
 * --------------------------------------
 * Initializes the current object to be a deep copy of the argument.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
    deepCopy(src);
}

/*
 * Implementation notes: assignment operator
 * Usage: q1 = q2;
 * -----------------------------------------
 * Assigns q2 to q1 so that the two priority queues function as independent
 * copies. For the PriorityQueue class, this kind of assignment requires
 * making a deep copy that includes the dynamic array.
 */

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
    if (this != &src) {
        if (array != NULL) delete[] array;
        deepCopy(src);
    }
    return *this;
}

/*
 * Implementation notes: expandCapacity
 * ------------------------------------
 * This method doubles the capacity of the priority queue by copying values from the
 * array into a new dynamic array. Because the new array has more space, values from
 * the old array are copied starting at the first element of the new array. This
 * method frees the heap memory associated with the old array as it is no longer in
 * use.
 */

void PriorityQueue::expandCapacity() {
    int count = size();
    capacity *= 2;
    ValuePriorityPair *oldArray = array;
    array = new ValuePriorityPair[capacity];
    for (int i = 0; i < count; i++) {
        array[i] = oldArray[(head + i) % capacity];
    }
    head = 0;
    tail = count;
    delete[] oldArray;
}

/*
 * Implementation notes: deepCopy
 * ------------------------------
 * This method copies all the data from the PriorityQueue passed as an argument
 * into the current object, including the values in the dynamic array.
 */

void PriorityQueue::deepCopy(const PriorityQueue & src) {
    int count = src.size();
    head = src.head;
    tail = src.tail;
    capacity = src.capacity;
    if (capacity < INITIAL_CAPACITY) capacity = INITIAL_CAPACITY;
    array = new ValuePriorityPair[capacity];
    for (int i = 0; i < count; i++) {
        array[i] = src.array[(head + i) % capacity];
    }
    head = 0;
    tail = count;
}
