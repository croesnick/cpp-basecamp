#ifndef _SIMPLE_FIFO_QUEUE_H_
#define _SIMPLE_FIFO_QUEUE_H_

#include <list>
#include <functional>

template <typename E>
class SimpleQueue {
public:
	SimpleQueue(); // TODO constructor with std::initializer_list

	void enqueue(const E &);
	/// Return std::nullptr if the queue is empty.
	E * dequeue();
	std::size_t size() const;

private:
	std::list<E> queue;
};

template <typename E>
SimpleQueue<E>::SimpleQueue() { }

template <typename E>
void SimpleQueue<E>::enqueue (const E & item) {
	queue.push_back(item);
}

template <typename E>
E * SimpleQueue<E>::dequeue() {
	E * first_item = nullptr;
	if (!queue.empty()) {
		first_item = new E(queue.front());
		queue.pop_front();
	}
	return first_item;
}

template <typename E>
std::size_t SimpleQueue<E>::size () const {
	return queue.size();
}

#endif
