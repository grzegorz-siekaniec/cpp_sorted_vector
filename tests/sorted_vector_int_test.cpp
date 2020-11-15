//
// Created by Grzegorz Siekaniec on 11/15/20.
//

#include "../src/sorted_vector.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::ElementsAre;

TEST(SortedVectorOfIntsWithDuplicates, ElementAreSortedAfterInsertion)
{
    sorted_vector<int, false> v;

    v.insert(4);
    v.insert(3);
    v.insert(5);
    v.insert(3);

    ASSERT_THAT(v, ElementsAre(3, 3, 4, 5));
}

TEST(SortedVectorOfIntsWithoutDuplicates, ElementAreSortedAfterInsertion)
{
    sorted_vector<int> v;

    v.insert(4);
    v.insert(3);
    v.insert(5);
    v.insert(3);

    ASSERT_THAT(v, ElementsAre(3, 4, 5));
}

//{
//for(auto & el: v)
//{
//std::cout << el << " ";
//}
//
//assert(v.contains(3));
//assert(!v.contains(6));
//auto itr = v.find(3);
//assert(itr != v.end());
//assert(*itr == 3);
//assert(v.find(6) == v.end());
//
//std::cout << "\n";
//
//std::vector<int> a {1, 3, 4, 2, 4, 5, -1, 0, -1};
//std::vector<int> unique_a {-1, 0, 1, 2, 3, 4, 5, };
//sorted_vector<int> sorted_a(a.begin(), a.end());
//assert(sorted_a.size() == unique_a.size());
//}