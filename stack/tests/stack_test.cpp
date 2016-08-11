#include "../include/stack.hpp"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

struct StackTest : ::testing::Test {
    public:
        StackN::Stack<int> test;
};

TEST_F(StackTest, HandleInput) {
    test.push(5);
    ASSERT_EQ(1, test.size());
    EXPECT_EQ(5, test.peek());
}

TEST_F(StackTest, HandleGrow) {
    for(int i = 0; i < 10; i++) {
        test.push(i);
    }
    ASSERT_EQ(10, test.size());
}

TEST_F(StackTest, HandleGrowAndPop) {
    for(int i = 0; i < 10; i++) {
        test.push(i);
    }
    for(int i = 9; i >= 0; i--) {
        EXPECT_EQ(i, test.pop());
    }
    ASSERT_EQ(0, test.size());
}

TEST_F(StackTest, HandlePeek) {
    test.push(4);
    int a = test.peek();
    a = 5;
    ASSERT_EQ(4, test.peek());
    ASSERT_EQ(5, a);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
