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

void test()
{
    sorted_vector<int> v;

    v.insert(4);
    v.insert(3);
    v.insert(5);
    v.insert(3);

    for(auto & el: v)
    {
        std::cout << el << " ";
    }

    assert(v.contains(3));
    assert(!v.contains(6));
    auto itr = v.find(3);
    assert(itr != v.end());
    assert(*itr == 3);
    assert(v.find(6) == v.end());

    std::cout << "\n";

    std::vector<int> a {1, 3, 4, 2, 4, 5, -1, 0, -1};
    std::vector<int> unique_a {-1, 0, 1, 2, 3, 4, 5, };
    sorted_vector<int> sorted_a(a.begin(), a.end());
    assert(sorted_a.size() == unique_a.size());
}

void test_pair() {
    sorted_vector<std::pair<int, int>> v;

    v.insert({1, 1});
    v.insert({3, 3});
    v.insert({5, 5});
    v.insert({3, 3});

    for(auto & el: v)
    {
        std::cout << "(" << el.first << " " << el.second << ") ";
    }

    assert(v.contains({3, 3}));
    assert(!v.contains({6, 6}));
    auto itr = v.find({3, 3});
    assert(itr != v.end());
    //assert(*itr == {3, 3});
    assert(v.find({6, 6}) == v.end());

    auto v_copy1 = v;
    assert(v_copy1 == v);

    std::cout << "\n";
}


struct IntStringPair
{
    int val_;
    std::string string_repr_;
};

struct compare_my
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

        sorted_vector<IntStringPair, compare_my> sorted_a(a.begin(), a.end());
        assert(sorted_a.size() == 4);
    }
}
