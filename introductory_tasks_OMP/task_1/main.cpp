#include "omp.h"
#include <iostream>

int main() {
  #pragma omp parallel
  {
    #pragma omp critical (cout)
    {
      std::cout << omp_get_thread_num() << ' ' << omp_get_num_threads() << " Hello World" << '\n';
    }
  }
}
