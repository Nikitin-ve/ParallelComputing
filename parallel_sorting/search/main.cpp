#include <pthread.h>
#include <iostream>
#include <vector>
#include <random>

#define THREADS 4
pthread_t threads[THREADS];

std::vector<int> a;
int n;
int search_elem;
int ind;
int thr;

void* search_function(void* arg) {
  int thread_part = *static_cast<int*>(arg);
  int start = thread_part * (n / THREADS);
  int end = (thread_part + 1) * (n / THREADS);
  for (int i = start; i < end; ++i) {
    if (a[i] == search_elem) {
      thr = thread_part;
      ind = i;
      pthread_cancel(*threads);
    }
  }
  return nullptr;
}

int main(int argc, char** argv) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::vector<int> th(THREADS);
  n = atoi(argv[1]);
  for (int i = 0; i < n; ++i) {
    a.push_back(gen() % static_cast<int>(1e3));
  }
  search_elem = a[gen() % n];
  for (int i = 0; i < THREADS; ++i) {
    th[i] = i;
    pthread_create(&threads[i], nullptr, search_function, &th[i]);
  }
  for (auto thread: threads) {
    pthread_join(thread, nullptr);
  }
  std::cout << "thread part: " << thr << " elem: " << search_elem << " index: " << ind << '\n';
}
