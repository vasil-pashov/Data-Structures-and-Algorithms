#include "gtest/gtest.h"
#include "../include/stack.hpp"

struct TestStack : ::testing::Test {
    StackN::Stack<int> test;
};

TEST_F(TestStack, HandleInsertSize) {
    ASSERT_EQ(0, test.size());
    test.push(1);
    ASSERT_EQ(1, test.size());
}

TEST_F(TestStack, HandlePeek) {
    ASSERT_EQ(0, test.size());
    test.push(5);
    EXPECT_EQ(5, test.peek());
    test.peek() = 10;
    EXPECT_EQ(10, test.peek());
}

TEST_F(TestStack, HandlePop) {
    for(int i = 0; i < 10; i++) {
        test.push(i);
    }
    ASSERT_EQ(10, test.size());
    for(int i = 9; i >= 0; i--) {
        EXPECT_EQ(i, test.pop());
    }
    ASSERT_EQ(0, test.size());
}

TEST_F(TestStack, HandleEmpty) {
    ASSERT_TRUE(test.empty());
    for(int i = 0; i < 10; i++) {
        test.push(i);
    }
    ASSERT_FALSE(test.empty());
    ASSERT_EQ(10, test.size());
    int i = 9;
    while (!test.empty()) {
        EXPECT_EQ(i, test.pop());
        i--;
    }
    ASSERT_EQ(0, test.size());
}

TEST_F(TestStack, HandleCopyConstruct) {
    for(int i = 0; i < 5; i++) {
        test.push(i);
    }
    StackN::Stack<int> s = test;
    ASSERT_EQ(test.size(), s.size());
    test.peek() = 5;
    ASSERT_EQ(4, s.peek());
    for(int i = 4; i >= 0; i--) {
        test.pop();
        EXPECT_EQ(i, s.peek());
        s.pop();
    }
}

TEST_F(TestStack, HandleOperatorEQ) {
    for(int i = 0; i < 5; i++) {
        test.push(i);
    }
    StackN::Stack<int> s;
    s = test;
    EXPECT_EQ(test.size(), s.size());
    test.peek() = 5;
    EXPECT_EQ(4, s.peek());
    for(int i = 4; i >= 0; i--) {
        test.pop();
        EXPECT_EQ(i, s.peek());
        s.pop();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
