//#include "/opt/homebrew/Cellar/libomp/18.1.5/include/omp.h"
#include "omp.h"
#include <iostream>

int main() {
  int ans = 0;
  #pragma omp parallel for ordered shared(ans) num_threads(omp_get_max_threads())
  for (int i = 0; i < omp_get_max_threads(); ++i) {
    #pragma omp ordered
    std::cout << omp_get_thread_num() << " ans: " << ++ans << '\n';
  }
}
