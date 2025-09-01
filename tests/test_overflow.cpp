#include <vector>
#include <limits>
#include <iostream>
#include "../src/lib.hpp"

int main() {
  //========= heap-buffer-overflow =================
  //std::vector<int> data = {1,2,3,4,5};
  //int n = data.size(); // -> provoziert Out-of-bounds
  //// int n = static_cast<int>(data.size());
  //std::cout << "Sum: " << sum_first_n(data, n) << "\n";

  //========= Memeory-Leak overflow =================
  new int[42];

  return 0;
}
