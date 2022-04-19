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

  void append(T x) {
    if (_size + 1 >= _capacity)
      resize(2*_capacity);
    data[_size] = x;
    _size += 1;
  }

  T get_at(size_t i) {
    if (i >= _size)
      throw std::out_of_range("get_at(): index out of range");
    return data[i];
  }

  void set_at(size_t i, T x) {
    if (i >= _size)
      throw std::out_of_range("get_at(): index out of range");
    data[i] = x;
  }

  T& operator[](size_t i) {
    if (i >= _size)
      throw std::out_of_range("get_at(): index out of range");
    return data[i];
  }

  void resize(size_t new_capacity) {
    auto tmp = new T[new_capacity]{0};
    _capacity = new_capacity;
    _size = std::min(_capacity, _size);
    std::copy_n(data, _size, tmp);
    delete[] data;
    data = tmp;
  }

  DynamicArray(size_t capacity=32) : _size{0}, _capacity{std::max(capacity, 32UZ)} {
    data = new T[capacity]{0};
  }

  ~DynamicArray() {
    delete[] data;
  }
};
