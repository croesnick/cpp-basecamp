#include "gtest/gtest.h"
#include "sample-project/sample.h"

TEST (SampleProjectTest, CheckIfGtestWorks) {
	EXPECT_EQ(1, 1);
}

TEST (SampleProjectTest, CheckForUniversalAnswer) {
	EXPECT_EQ(42, universal_answer(23));
}
