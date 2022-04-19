#include <algorithm>
#include <utility>
#include <vector>

using std::vector;

template<typename T=int>
class MinHeap {
private:
  T* data;
  size_t size;
  size_t capacity;

public:
  vector<T> elems() {
    auto out = vector<T>();
    if (size) out.insert(end(out), &data[1], &data[size]);
    return out;
  }

  size_t empty() {
    return size <= 0;
  }

  size_t len() {
    return size;
  }

  void resize(size_t new_capacity) {
    auto tmp = new int[new_capacity + 1]{0};
    auto n = new_capacity > capacity ? size + 1 : new_capacity + 1;
    std::copy_n(data, n, tmp);
    delete[] data;
    data = tmp;
    capacity = new_capacity;
  }

  int min() {
    // die_if(size >= capacity);
    if (size <= 0)
      throw std::runtime_error("called min() on empty container");
    return data[1];
  }

  size_t parent(size_t i) {
    return std::max(i/2, 1UZ);
  }

  size_t left(size_t i) {
    return std::min(2*i, size);
  }

  size_t right(size_t i) {
    return std::min(left(i) + 1, size);
  }

  void insert(T x) {
    size += 1;

    if (size >= capacity)
      resize(2*capacity);

    data[size] = x;

    for (auto i = size; ;) {
      auto p = parent(i);
      if (data[i] >= data[p]) break;
      std::swap(data[i], data[p]);
      i = p;
    }
  }

  void del() {
    if (size < 1) return;
    data[1] = data[size];

    for (size_t i = 1; ;) {
      auto l = left(i), r = right(i);
      auto m = data[l] < data[r] ? l : r;
      if (data[i] <= data[m]) break;
      std::swap(data[i], data[m]);
      i = m;
    }
    if (4*size <= capacity)
      resize(capacity/2);
    size -= 1;
  }

  size_t get_capacity() {
    return capacity;
  }

  MinHeap(size_t capacity=32) : size{0}, capacity{std::max(capacity, 32UZ)} {
    data = new int[capacity + 1]{0};
  }

  ~MinHeap() {
    delete[] data;
  }
};
