//
// Created by gsiekaniec on 10/20/19.
//

//#include <gtest>

#include <iostream>
#include <string>
#include <cassert>
#include "sorted_vector_test.h"
#include "../src/sorted_vector.h"
#include <set>


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


void test_struct() {
    //std::set<IntStringPair, compare_my> v;
    sorted_vector<IntStringPair, compare_my> v;
    v.emplace_back(IntStringPair{4, "four"});
    v.insert(IntStringPair{1, "one"});
    v.emplace_back(IntStringPair{-1, "minus one"});
    v.emplace_back(IntStringPair{-1, "minus one"});
    v.emplace_back(IntStringPair{1, "minus one"});
    v.emplace_back(IntStringPair{2, "two"});

    for(const auto & el: v) {
        std::cout << el.val_ << " " << el.string_repr_ << "\n";
    }

    auto v_copy1 = v;
    auto v_copy2(v);

    assert(v_copy1.size() == v.size());
    assert(v_copy2.size() == v.size());
    assert(v_copy2 == v);

    v.emplace_back(IntStringPair{3, "three"});
    for(const auto & el: v) {
        std::cout << el.val_ << " " << el.string_repr_ << "\n";
    }

    assert(v_copy1 != v);
    assert(v_copy2 != v);

    {
        std::vector<IntStringPair> a {
                IntStringPair{4, "four"},
                IntStringPair{1, "one"},
                IntStringPair{-1, "minus one"},
                IntStringPair{-1, "minus one"},
                IntStringPair{1, "minus one"},
                IntStringPair{2, "two"},
        };

        sorted_vector<IntStringPair, IntStringPairCmp> sorted_a(a.begin(), a.end());
        assert(sorted_a.size() == 4);
    }
}
