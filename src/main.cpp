#include <iostream>
#include <set>
#include "../tests/sorted_vector_test.h"

// Use some micro benchamrk library to test performance

int main() {

    test();
    test_pair();
    test_struct();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}