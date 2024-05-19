#include <iostream>
#include <cmath>
#include <vector>

const int N = 1e2;
const int M = 2 * 1e2;

int main() {
  std::vector<std::vector<long double>> u(M + 1, std::vector<long double>(N + 1));
  for (int i = 0; i <= M; ++i) {
    if (i % 2 == 0) {
      u[i][0] = 1;
    } else {
      u[i][0] = -1;
    }
  }
  for (int i = 0; i <= N; ++i) {
    u[0][i] = exp(-i);
  }
  for (int k = 0; k < M; ++k) {
    for (int m = 1; m <= N; ++m) {
      u[k + 1][m] = (1.0 * k) / (M * M) + (1.0 * m) / (M * N) - (1.0 * N) / M * (u[k][m] - u[k][m - 1]) + u[k][m];
    }
  }
  for (int i = 0; i <= M; ++i) {
    for (int j = 0; j <= N; ++j) {
      std::cout << u[i][j] << ' ';
    }
    std::cout << '\n';
  }
}
