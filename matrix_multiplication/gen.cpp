#include <fstream>

void Generate(int N, int M, std::ofstream& out) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (out.is_open()) {
        out << rand() - rand() << ' ';
      }
    }
    out << '\n';
  }
}

int main(int argc, char** argv) {
  std::ofstream out;
  out.open("matrix.txt");
  int N = atoi(argv[1]);
  int M = atoi(argv[2]);
  int K = atoi(argv[3]);
  out << N << ' ' << M << ' ' << K << '\n';
  Generate(N, M, out);
  Generate(M, K, out);
  out.close();
}
