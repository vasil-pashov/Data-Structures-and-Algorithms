#include <iostream>
#include "../include/linked_list.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace LinkedListN;

struct TestList : ::testing::Test {
    public:
        LinkedList<int> v;
        TestList() {
            for(int i = 0; i < 3; i++) {
                v.push_back(i);
            }           
        }
};

TEST_F(TestList, HandleInputSizeCap) {
    EXPECT_EQ(3, v.size());
}

TEST_F(TestList, HandleInputValues) {
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(i, v[i]);
    }
}

TEST_F(TestList, HandleErase) {
    v.erase(1);
    ASSERT_EQ(2, v.size());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(2, v[1]);
}

TEST_F(TestList, HandleEraseFirst) {
    v.erase(0);
    ASSERT_EQ(2, v.size());
    int i = 1;
    for(LinkedList<int>::iterator it = v.begin(); it != v.end(); ++it, i++) {
        EXPECT_EQ(i, *it);
    }
}

TEST_F(TestList, HandleEraseLast) {
    v.erase(2);
    ASSERT_EQ(2, v.size());
    int i = 0;
    for(LinkedList<int>::iterator it = v.begin(); it != v.end(); ++it, i++) {
        EXPECT_EQ(i, *it);
    }
}
//========================================================
TEST_F(TestList, HandlePopBack) {
    v.pop_back();
    ASSERT_EQ(2, v.size());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(1, v[1]);
    
}

TEST_F(TestList, HandleCopyConstruct) {
    LinkedList<int> v2 = v;
    ASSERT_EQ(v.size(), v2.size());
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(v[i], v2[i]);
    }
}

TEST_F(TestList, DeepCopyCheck) {
    LinkedList<int> v2 = v;
    v2[0] = 5;
    ASSERT_NE(v[0], v[1]);
}

TEST_F(TestList, HandleCopyAssign) {
    LinkedList<int> v2;
    v2 = v;
    ASSERT_EQ(v.size(), v2.size());
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(v[i], v2[i]);
    }
}

TEST_F(TestList, DeepCopyAssignCheck) {
    LinkedList<int> v2 = v;
    v2[0] = 5;
    ASSERT_NE(v[0], v[1]);
}

TEST_F(TestList, HandleInsert) {
    v.insert(1, 100);
    ASSERT_EQ(4, v.size());
    EXPECT_EQ(0, v[0]);
    EXPECT_EQ(100, v[1]);
    EXPECT_EQ(1, v[2]);
    EXPECT_EQ(2, v[3]);
}


TEST_F(TestList, HandleClear) {
    v.clear();
    EXPECT_EQ(0, v.size());
}




int main(int argc, char **argv) {
    cout<<argc<<argv<<endl;
    LinkedList<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.erase(2);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

