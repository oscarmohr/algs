#include <algorithm>
#include <cstddef>

template<typename T=int>
class DynamicArray {
private:
  T* data;
  size_t _size;
  size_t _capacity;

public:
  size_t size() {
    return _size;
  }

  size_t capacity() {
    return _capacity;
  }

  T& back() {
    if (_size == 0) 
      throw std::out_of_range("back(): empty container");
    return data[_size - 1];
  }

  void push_back(T x) {
    _size += 1;

    if (_size >= _capacity)
      resize(2 * _capacity);

    data[_size - 1] = x;
  }

  void pop_back() {
    if (!_size) return;
    _size -= 1;

    if (_capacity > 4 * _size)
      resize(_capacity / 2);
  }

  T& operator[](size_t i) {
    if (i >= _size)
      throw std::out_of_range("operator[](): index out of range");

    return data[i];
  }

  void resize(size_t new_capacity) {
    if (!new_capacity)
      throw std::runtime_error("resize(): resize to 0");

    _capacity = new_capacity;
    _size = std::min(_capacity, _size);

    auto tmp = new T[_capacity];
    std::copy_n(data, _size, tmp);

    delete[] data;
    data = tmp;
  }

  DynamicArray(size_t capacity=32) : _size{0}, _capacity{std::max(capacity, 32UZ)} {
    data = new T[capacity];
  }

  DynamicArray(T* arr, size_t n) : _size{n}, _capacity{std::max(n, 32UZ)} {
    data = new T[_capacity];
    std::copy_n(arr, n, data);
  }

  ~DynamicArray() {
    delete[] data;
  }
};
