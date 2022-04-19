#include "../include/util.hpp"
#include "DynamicArray.hpp"
#include "../MinHeap/MinHeap.hpp"

using namespace util;

int main() {
  auto a = DynamicArray();
  print("initial capacity of array: ", a.capacity());
  print("number of elements in array: ", a.size());

  print("inserting element at the end of the array...");
  a.append(1);

  print("size is now ", a.size());
  print("accessing first element ", a[0]);

  print("inserting powers of two, one by one...");
  for (auto i = 0; i < 31; i++) {
    a.append(1 << i);
    print("inserted ", 1 << i);
  }
  print("last element inserted is ", a.back());

  print("adding large number of elements...");
  for (auto i = 0; i < 1e5; i++) {
    auto cap = a.capacity();
    a.append(i);
    if (auto new_cap = a.capacity(); new_cap > cap)
      print("resized from ", cap, " to ", new_cap);
  }

  print("array now has ", a.size(), " elements");

  auto h = MinHeap(a.size());

  print("sorting the array with a MinHeap...");

  for (size_t i = 0; i < a.size(); i++) {
    h.insert(a[i]);
  } 

  for (size_t i = 0; i < a.size(); i++) {
    a[i] = h.min();
    h.del();
  }
  
  print("printing out first 32 elements in sorted order... ",
        "powers of two should appear twice");
  for (size_t i = 0; i < 32; i++) {
    put(a[i], " ");
  }
}
