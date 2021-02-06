//
// Created by gsiekaniec on 2/3/21.
//

#include "../src/sorted_vector.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::Pointwise;
using ::testing::get;

struct IntStringPair
{
    int val_;
    std::string string_repr_;
};

struct IntStringPairCmp
{
    bool operator()(const IntStringPair &lhs, const IntStringPair &rhs) const
    {
        return lhs.val_ < rhs.val_;
    }
};

MATCHER(IntStringPairEq, "") {
    return IntStringPairCmp()(get<0>(arg), get<1>(arg)) == 0
        && IntStringPairCmp()(get<1>(arg), get<0>(arg)) == 0;
}

TEST(SortedVectorOfPairOfIntAndWithCustomSorter, ElementAreSortedAfterEmplaceBack)
{
    sorted_vector<IntStringPair, true, IntStringPairCmp> v;
    v.emplace_back(IntStringPair{4, "four"});
    v.insert(IntStringPair{1, "one"});
    v.emplace_back(IntStringPair{-1, "minus one"});
    v.emplace_back(IntStringPair{-1, "minus one"});
    v.emplace_back(IntStringPair{1, "minus one"}); // on purpose
    v.emplace_back(IntStringPair{2, "two"});
    v.emplace_back(IntStringPair{0, "zero"});

    ASSERT_THAT(
            v,
            Pointwise(
                    IntStringPairEq(),
                    {
                        IntStringPair{-1, "minus one"},
                        IntStringPair{0, "zero"},
                        IntStringPair{1, "one"},
                        IntStringPair{2, "two"},
                        IntStringPair{4, "four"}
                    }
            ));
}

TEST(SortedVectorOfPairOfIntAndWithCustomSorter, ConstructorWithInitializerListWorks)
{
    sorted_vector<IntStringPair, true, IntStringPairCmp> v{
        IntStringPair{1, "one"},
        IntStringPair{2, "two"},
        IntStringPair{4, "four"},
        IntStringPair{-1, "minus one"},
        IntStringPair{0, "zero"}
    };

    ASSERT_THAT(
            v,
            Pointwise(
                    IntStringPairEq(),
                    {
                            IntStringPair{-1, "minus one"},
                            IntStringPair{0, "zero"},
                            IntStringPair{1, "one"},
                            IntStringPair{2, "two"},
                            IntStringPair{4, "four"}
                    }
            ));
}

TEST(SortedVectorOfPairOfIntAndWithCustomSorter, CopyConstructorWorks)
{
    sorted_vector<IntStringPair, true, IntStringPairCmp> v{
        IntStringPair{2, "two"},
        IntStringPair{4, "four"},
        IntStringPair{-1, "minus one"},
        IntStringPair{0, "zero"},
        IntStringPair{1, "one"}
    };

    auto v_copy(v);

    ASSERT_THAT(
            v_copy,
            Pointwise(
                    IntStringPairEq(),
                    {
                            IntStringPair{-1, "minus one"},
                            IntStringPair{0, "zero"},
                            IntStringPair{1, "one"},
                            IntStringPair{2, "two"},
                            IntStringPair{4, "four"}
                    }
            ));

    ASSERT_EQ(v.size(), v_copy.size());

    ASSERT_EQ(v, v_copy);
}

TEST(SortedVectorOfPairOfIntAndWithCustomSorter, AssignmentOperatorWorks)
{
    sorted_vector<IntStringPair, true, IntStringPairCmp> v{
        IntStringPair{2, "two"},
        IntStringPair{4, "four"},
        IntStringPair{-1, "minus one"},
        IntStringPair{0, "zero"},
        IntStringPair{1, "one"}
    };

    auto v_copy = v;

    ASSERT_THAT(
            v_copy,
            Pointwise(
                    IntStringPairEq(),
                    {
                            IntStringPair{-1, "minus one"},
                            IntStringPair{0, "zero"},
                            IntStringPair{1, "one"},
                            IntStringPair{2, "two"},
                            IntStringPair{4, "four"}
                    }
            ));

    ASSERT_EQ(v.size(), v_copy.size());

    ASSERT_EQ(v, v_copy);
}