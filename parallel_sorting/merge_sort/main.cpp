#include <pthread.h>
#include <iostream>
#include <vector>

#define THREADS 4

std::vector<int> a;
int n;

void Merge(int low, int high, int mid) {
  int i, j, k, temp[high - low + 1];
  i = low;
  k = 0;
  j = mid + 1;
  while (i <= mid && j <= high) {
    if (a[i] < a[j]) {
      temp[k] = a[i];
      ++k;
      ++i;
    }
    else {
      temp[k] = a[j];
      ++k;
      ++j;
    }
  }
  while (i <= mid) {
    temp[k] = a[i];
    ++k;
    ++i;
  }
  while (j <= high) {
    temp[k] = a[j];
    ++k;
    ++j;
  }
  for (i = low; i <= high; ++i) {
    a[i] = temp[i - low];
  }
}

void MergeSort(int low, int high) {
  int mid;
  if (low < high) {
    mid=(low+high)/2;
    MergeSort(low, mid);
    MergeSort(mid+1, high);
    Merge(low, high, mid);
  }
}

void* sort_function(void* arg) {
  int thread_part = *static_cast<int*>(arg);
  int start = thread_part * (n / THREADS);
  int end = (thread_part + 1) * (n / THREADS) - 1;
  MergeSort(start, end);
  return nullptr;
}

int main(int argc, char** argv) {
  pthread_t threads[THREADS];
  std::vector<int> th(THREADS);
  n = atoi(argv[1]);
  for (int i = 0; i < n; ++i) {
    a.push_back(rand() % static_cast<int>(1e3));
  }
  for (int i = 0; i < THREADS; ++i) {
    th[i] = i;
    pthread_create(&threads[i], nullptr, sort_function, &th[i]);
  }
  for (auto thread: threads) {
    pthread_join(thread, nullptr);
  }
  for (int i = 1; i < THREADS; ++i) {
    Merge((i - 1) * (n / THREADS), (i + 1) * (n / THREADS) - 1, i * (n / THREADS) - 1);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << ' ';
  }
  std::cout << '\n';
}
