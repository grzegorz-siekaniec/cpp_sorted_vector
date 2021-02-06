//
// Created by gsiekaniec on 2/3/21.
//

#include "../src/sorted_vector.h"
#include "gtest/gtest.h"

TEST(SortedVectorOfPairOfIntsWithDuplicates, ElementAreSortedAfterInsertion)
{
    sorted_vector<std::pair<int, int>> v;

    v.insert({1, 1});
    v.insert({3, 3});
    v.insert({5, 5});
    v.insert({3, 3});

    ASSERT_TRUE(v.contains({3, 3}));
    ASSERT_TRUE(!v.contains({6, 6}));
    ASSERT_NE(v.find({3, 3}), v.end());
    ASSERT_EQ(v.find({6, 6}), v.end());

    auto v_copy(v);
    ASSERT_EQ(v_copy, v);
}