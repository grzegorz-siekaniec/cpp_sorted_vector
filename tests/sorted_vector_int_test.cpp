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

TEST(SortedVectorOfIntsWithoutDuplicates, ElementAreSortedAndUniqueIfProvidedByConstructor)
{
    std::vector<int> a {1, 3, 4, 2, 4, 5, -1, 0, -1};
    std::vector<int> unique_a {-1, 0, 1, 2, 3, 4, 5};
    sorted_vector<int> sorted_a(a.begin(), a.end());
    ASSERT_THAT(sorted_a,
                testing::Pointwise(testing::Eq(), unique_a));
}