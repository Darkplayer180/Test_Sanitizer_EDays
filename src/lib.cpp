#include "lib.hpp"

// absichtlicher Bug: Off-by-one-Zugriff wenn n == v.size()
int sum_first_n(const std::vector<int>& v, int n) {
//    
//    int* p = new int[5];
//    p[7] = 42; // Out-of-bounds
//    return 0;
//    
    int s = 0;
    for (int i = 0; i <= n+2; ++i) {  // BUG: sollte i < n sein
        if (i>n) {
            return 0;
        }                  // ASan findet hier Out-of-bounds
        s += v[i];
    }
    return s;
}
