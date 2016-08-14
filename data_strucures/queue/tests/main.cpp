#include "gtest/gtest.h"
#include "../include/queue.hpp"
	
struct TestQueue : ::testing::Test {
    QueueN::Queue<int> test;
};

TEST_F(TestQueue, HandleInsertSize) {
    ASSERT_EQ(0, test.size());
    test.push(1);
    ASSERT_EQ(1, test.size());
}

TEST_F(TestQueue, HandlePeek) {
    ASSERT_EQ(0, test.size());
    test.push(5);
    EXPECT_EQ(5, test.peek());
    test.peek() = 10;
    EXPECT_EQ(10, test.peek());
}

TEST_F(TestQueue, HandlePop) {
    for(int i = 0; i < 10; i++) {
        test.push(i);
    }
    ASSERT_EQ(10, test.size());
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(i, test.pop());
    }
    ASSERT_EQ(0, test.size());
}

TEST_F(TestQueue, HandleEmpty) {
    ASSERT_TRUE(test.empty());
    for(int i = 0; i < 10; i++) {
        test.push(i);
    }
    ASSERT_FALSE(test.empty());
    ASSERT_EQ(10, test.size());
    int i = 0;
    while (!test.empty()) {
        EXPECT_EQ(i, test.pop());
        i++;
    }
    ASSERT_EQ(0, test.size());
}

TEST_F(TestQueue, HandleCopyConstruct) {
    for(int i = 0; i < 5; i++) {
        test.push(i);
    }
    QueueN::Queue<int> q = test;
    EXPECT_EQ(test.size(), q.size());
    test.peek() = 5;
    EXPECT_EQ(0, q.peek());
    for(int i = 0; i < 5; i++) {
        test.pop();
        EXPECT_EQ(i, q.peek());
        q.pop();
    }
}

TEST_F(TestQueue, HandleOperatorEQ) {
    for(int i = 0; i < 5; i++) {
        test.push(i);
    }
    QueueN::Queue<int> q;
    q = test;
    EXPECT_EQ(test.size(), q.size());
    test.peek() = 5;
    EXPECT_EQ(0, q.peek());
    for(int i = 0; i < 5; i++) {
        test.pop();
        EXPECT_EQ(i, q.peek());
        q.pop();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
