#include <iostream>
#include "../include/vector.hpp"
#include "gtest/gtest.h"

//using namespace std;
using namespace Vector;

struct TestVector : ::testing::Test {
    public:
        vector<int> v;
        TestVector() {
            for(int i = 0; i < 3; i++) {
                v.push_back(i);
            }           
        }
};

TEST_F(TestVector, HandleInputSizeCap) {
    EXPECT_EQ(3, v.size());
    EXPECT_EQ(4, v.capacity());
}

TEST_F(TestVector, HandlePushBackGrowSizeCap) {
    v.push_back(4); 
    v.push_back(5); 
    EXPECT_EQ(5, v.size());
    EXPECT_EQ(8, v.capacity());
}

TEST_F(TestVector, HandleInputValues) {
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(i, v[i]);
    }
}

TEST_F(TestVector, HandleErase) {
    v.erase(1);
    ASSERT_EQ(2, v.size());
    ASSERT_EQ(4, v.capacity());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(2, v[1]);
}

TEST_F(TestVector, HandlePopBack) {
    v.pop_back();
    ASSERT_EQ(2, v.size());
    ASSERT_EQ(4, v.capacity());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(1, v[1]);
    
}

TEST_F(TestVector, HandleCopyConstruct) {
    vector<int> v2 = v;
    ASSERT_EQ(v.size(), v2.size());
    ASSERT_EQ(v.capacity(), v2.capacity());
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(v[i], v2[i]);
    }
}

TEST_F(TestVector, DeepCopyCheck) {
    vector<int> v2 = v;
    v2[0] = 5;
    ASSERT_NE(v[0], v[1]);
}

TEST_F(TestVector, TestShrinkToFit) {
    v.erase(1);
    v.shrink_to_fit();
    ASSERT_EQ(2, v.size());
    ASSERT_EQ(2, v.capacity());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(2, v[1]);
}

TEST_F(TestVector, HandleCopyAssign) {
    vector<int> v2;
    v2 = v;
    ASSERT_EQ(v.size(), v2.size());
    ASSERT_EQ(v.capacity(), v2.capacity());
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(v[i], v2[i]);
    }
}

TEST_F(TestVector, DeepCopyAssignCheck) {
    vector<int> v2 = v;
    v2[0] = 5;
    ASSERT_NE(v[0], v[1]);
}

TEST_F(TestVector, HandleInsert) {
    v.insert(1, 100);
    ASSERT_EQ(4, v.size());
    ASSERT_EQ(4, v.capacity());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(100, v[1]);
    EXPECT_EQ(1, v[2]);
    EXPECT_EQ(2, v[3]);
}

TEST_F(TestVector, HandleInsertGrow) {
    v.insert(1, 100);
    v.insert(2, -5);
    ASSERT_EQ(5, v.size());
    ASSERT_EQ(8, v.capacity());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(100, v[1]);
    EXPECT_EQ(-5, v[2]);
    EXPECT_EQ(1, v[3]);
    EXPECT_EQ(2, v[4]);

}

TEST_F(TestVector, HandleClear) {
    v.clear();
    EXPECT_EQ(0, v.size());
    EXPECT_EQ(4, v.capacity());
}

TEST_F(TestVector, HandleIteratorLEPP) {
    int i = 0;
    for(vector<int>::iterator it = v.begin(); it < v.end(); it++, i++) {
        EXPECT_EQ(i, *it);
    }
}

TEST_F(TestVector, HandleIteratorAccess) {
    vector<int>::iterator it = v.begin();
    for(int i = 0; static_cast<unsigned long long>(i) < v.size();i++) {
        EXPECT_EQ(i, it[i]);
        it[i] = it[i] + 1;
        EXPECT_EQ(i+1, it[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
