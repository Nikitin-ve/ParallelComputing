#include "omp.h"
#include <iostream>

int main(int argc, char** argv) {
  int n = atoi(argv[1]);
  long double ans = 0;
  #pragma omp parallel
  {
    long double local_ans = 0;
    #pragma omp for
    for (int i = 1; i <= n; ++i) {
      local_ans += 1.0 / i;
    }
    #pragma omp atomic
    ans += local_ans;
  }
  std::cout << ans << '\n';
}
