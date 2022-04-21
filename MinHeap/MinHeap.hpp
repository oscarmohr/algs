#include <algorithm>
#include <utility>
#include <vector>

template<typename T=int>
class MinHeap {
private:
  T* data;
  size_t _size;
  size_t _capacity;

  // leaves reside in data[_size / 2], ..., data[_size - 1]
  bool is_leaf(size_t i) {
    return _size / 2 <= i && i <= _size - 1;
  }

  // heap-property of subtree rooted at i
  bool is_heap(size_t i=0) {
    if (i >= _size || is_leaf(i))
      return true;

    // minChild is defined for internal nodes
    if (data[i] > data[minChild(i)])
      return false;

    return is_heap(left(i)) && is_heap(right(i));
  }

  size_t parent(size_t i) {
    return (i - 1) / 2;
  }

  size_t left(size_t i) {
    return 2 * i + 1;
  }

  size_t right(size_t i) {
    return left(i) + 1;
  }

  size_t minChild(size_t i) {
    // assumes i is internal node
    if (i >= _size || is_leaf(i))
      throw std::out_of_range("minChild(): index out of range");

    size_t l = left(i), r = right(i);
    return r >= _size || data[l] <= data[r] ? l : r;
  }

  // makes i root of a subheap, assuming its children are heaps
  void bubbleDown(size_t i) {
    if (i >= _size || is_leaf(i)) return;
    if (auto m = minChild(i); data[i] > data[m]) {
      std::swap(data[i], data[m]);
      bubbleDown(m);
    }
  }

  void bubbleUp(size_t i) {
    if (!i) return;
    if (auto p = parent(i); data[i] < data[p]) {
      std::swap(data[i], data[p]);
      bubbleUp(p);
    }
  }

  void heapify() {
    if (_size <= 1) return;

    // bubble down internal nodes
    for (int i = _size / 2 - 1; i >= 0; i--)
      bubbleDown(i);
  }

public:
  std::vector<T> elems() {
    auto elems = std::vector<T>();
    elems.reserve(_size);

    for (size_t i = 0; i < _size; i++)
      elems.push_back(data[i]);

    return elems;
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

    auto tmp = new int[_capacity];
    std::copy_n(data, _size, tmp);

    delete[] data;
    data = tmp;
  }

  int min() {
    if (!_size)
      throw std::runtime_error("called min() on empty container");

    return data[0];
  }

  void insert(T x) {
    _size += 1;

    if (_size >= _capacity)
      resize(2 * _capacity);

    data[_size - 1] = x;

    bubbleUp(_size - 1);
  }

  void pop_min() {
    if (!_size) return;
    data[0] = data[_size - 1];

    _size -= 1;

    bubbleDown(0);

    if (_capacity > 4 * _size)
      resize(_capacity/2);
  }

  MinHeap(size_t capacity=32) : _size{0}, _capacity{std::max(capacity, 32UZ)} {
    data = new int[_capacity];
  }

  MinHeap(T* arr, size_t n) : _size{n}, _capacity{2*_size} {
    data = new int[_capacity];
    std::copy_n(arr, _size, data);
    heapify();
  }

  ~MinHeap() {
    delete[] data;
  }
};
