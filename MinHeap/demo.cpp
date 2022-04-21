#include "../include/util.hpp"
#include "MinHeap.hpp"

using namespace util;

int main() {
  // create new MinHeap with initial capacity of 100
  auto h = MinHeap(100);

  print("inserting elements...");
  h.insert(8);
  h.insert(231);

  // efficiently get minimum value in MinHeap. min = 8
  print("min is ", h.min());

  print("inserting some more elements...");
  h.insert(16);
  h.insert(-1);

  // min is now -1
  print("min is now ", h.min());

  // remove minimal element
  print("removing minimum.");
  h.pop_min();

  // min is back to 8 again
  print("min is now again ", h.min());

  print("Sorting an array: ");
  constexpr size_t n = 32;
  auto arr = new int[n];

  for (size_t i = 0; i < n; i++)
    arr[i] = rand() % n;

  print("The array:");
  for (size_t i = 0; i < n; i++) {
    put(arr[i], ' ');
  }
  print('\n');

  auto h2 = MinHeap(arr, n);

  print("repeatedly printing its minimal element:");
  for (size_t i = 0; i < n; i++) {
    put(h2.min(), ' ');
    h2.pop_min();
  }
  print();
}
