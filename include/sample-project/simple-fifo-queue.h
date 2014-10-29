#ifndef _SIMPLE_FIFO_QUEUE_H_
#define _SIMPLE_FIFO_QUEUE_H_

#include <list>
#include <functional>

/**
 * A simple 'first in first out' (FIFO) queue implementation.
 */
template <typename E>
class SimpleQueue {
public:
	SimpleQueue(); // TODO additional constructor with std::initializer_list
	
	/**
	 * Add a new element to the end of the queue.
	 * @param[in] e The element to be inserted in the queue.
	 */
	void enqueue(const E & e);
	
	/**
	 * Returns the first (top) element from the queue and also removes it from
	 * the queue.
	 * @return A pointer to the first (top) element of the queue if the queue
	 *         is non-empty; otherwise nullptr.
	 */
	E * dequeue();
	
	/**
	 * Returns the number of elements currently placed in the queue.
	 * @return Number of elements in the queue.
	 */
	std::size_t size() const;

private:
	/**
	 * The queue is modelled by a list: New elements are pushed back to the
	 * end of the list, while the oldest elements are on the front of the 
	 * list.
	 */
	std::list<E> queue;
};

template <typename E>
SimpleQueue<E>::SimpleQueue() { }

template <typename E>
void SimpleQueue<E>::enqueue (const E & e) {
	queue.push_back(e);
}

template <typename E>
E * SimpleQueue<E>::dequeue() {
	E * top = nullptr;
	if (!queue.empty()) {
		top = new E(queue.front());
		queue.pop_front();
	}
	return top;
}

template <typename E>
std::size_t SimpleQueue<E>::size () const {
	return queue.size();
}

#endif
