#include <algorithm>
#include <utility>
#include <vector>

template<typename T=int>
class MinHeap {
private:
  T* data;
  size_t _size;
  size_t _capacity;

  size_t parent(size_t i) {
    return std::max(i/2, 1UZ);
  }

  size_t left(size_t i) {
    return std::min(2*i, _size);
  }

  size_t right(size_t i) {
    return std::min(left(i) + 1, _size);
  }

  size_t minChild(size_t i) {
    size_t l = left(i), r = right(i);
    return data[l] <= data[r] ? l : r;
  }

  void bubbleDown(size_t i) {
    for (size_t m = minChild(i); data[i] > data[m]; i = m, m = minChild(i))
      std::swap(data[i], data[m]);
  }

  void bubbleUp(size_t i) {
    for (size_t p = parent(i); data[i] < data[p]; i = p, p = parent(i))
      std::swap(data[i], data[p]);
  }

public:
  std::vector<T> elems() {
    auto out = std::vector<T>();
    if (_size) {
      out.reserve(_size);
      out.insert(end(out), &data[1], &data[_size]);
    }
    return out;
  }

  size_t empty() {
    return !_size;
  }

  size_t size() {
    return _size;
  }

  size_t capacity() {
    return _capacity;
  }

  void resize(size_t new_capacity) {
    if (!new_capacity)
      throw std::runtime_error("resize(): resize to 0");

    _capacity = new_capacity;
    _size = std::min(_capacity, _size);

    auto tmp = new int[_capacity + 1];
    std::copy_n(data, _size + 1, tmp);

    delete[] data;
    data = tmp;
  }

  int min() {
    if (!_size)
      throw std::runtime_error("called min() on empty container");

    return data[1];
  }

  void insert(T x) {
    _size += 1;

    if (_size >= _capacity)
      resize(2 * _capacity);

    data[_size] = x;

    bubbleUp(_size);
  }

  void pop_min() {
    if (!_size) return;
    data[1] = data[_size];

    _size -= 1;

    bubbleDown(1);

    if (_capacity > 4 * _size)
      resize(_capacity/2);
  }

  MinHeap(size_t capacity=32) : _size{0}, _capacity{std::max(capacity, 32UZ)} {
    data = new int[_capacity + 1];
  }

  ~MinHeap() {
    delete[] data;
  }
};
