//#include "/opt/homebrew/Cellar/libomp/18.1.5/include/omp.h"
#include "omp.h"
#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
  auto itime = omp_get_wtime();
  int N;
  if (argv[1] == NULL) {
    N = omp_get_max_threads();
  } else {
    N = atoi(argv[1]);
  }
  int n = 0, m = 0, k = 0;
  std::ifstream in("matrix.txt");
  if (in.is_open()) {
    in >> m >> n >> k;
  } else {
    std::cout << "matrix.txt not found" << '\n';
    return 0;
  }
  if (n == 0 || m == 0 || k == 0) {
    std::cout << "Error: incorrect size" << '\n';
    return 0;
  }
  std::vector<std::vector<int>> A(m, std::vector<int>(n));
  std::vector<std::vector<int>> B(n, std::vector<int>(k));
  std::vector<std::vector<long long>> C(m, std::vector<long long>(k, 0));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      in >> A[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j) {
      in >> B[i][j];
    }
  }
  in.close();
  #pragma omp parallel for collapse(2) shared(A, B, C) num_threads(N)
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      for (int t = 0; t < n; ++t) {
        C[i][j] += A[i][t] * B[t][j];
      }
    }
  }
  auto ftime = omp_get_wtime();
  std::cout << "Execution time: " << ftime - itime << " Size: " << m << ' ' << n << ' ' << k << '\n';
  std::cout << '\n' << "Initial matrix:" << '\n' << '\n';
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << A[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k; ++j) {
      std::cout << B[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n' << "Product: " << '\n' << '\n';
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < k; ++j) {
      std::cout << C[i][j] << ' ';
    }
    std::cout << '\n';
  }
}
