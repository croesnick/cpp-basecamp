#include "sample-project/simple-fifo-queue.h"
#include "gtest/gtest.h"
#include <functional>

class SimpleQueueTest : public ::testing::Test {
public:
	virtual void SetUp() {
		q1.enqueue(-1);
		// inserts sequence 1, -3, 5, -7, 9, ..., -17
		for (int i = 0; i < 10; ++i) {
			q3.enqueue( (i%2 ? 0 : -1) * (2*i-1) );
		}
	}

	SimpleQueue<int> q0, q1, q3;
};

TEST_F (SimpleQueueTest, InitiallyEmpty) {
	EXPECT_EQ (0, q0.size());
	EXPECT_EQ (nullptr, q0.dequeue());
}

TEST_F (SimpleQueueTest, AcceptsDuplicates) {
	EXPECT_EQ (1, q1.size());
	q1.enqueue(-1);
	EXPECT_EQ (2, q1.size());
	int * first_item = q1.dequeue();
	ASSERT_NE (nullptr, first_item);
	EXPECT_EQ (-1, *first_item);
	delete first_item;
}

TEST_F (SimpleQueueTest, OrderPreserving) {
	EXPECT_EQ (10, q3.size());
	int * item = nullptr;
	for (int i = 0; i < 10; ++i) {
		item = q3.dequeue();
		ASSERT_NE (nullptr, item);
		EXPECT_EQ ((i%2 ? 0 : -1) * (2*i-1), *item);
		delete item;
	}
	EXPECT_EQ (0, q3.size());
}
