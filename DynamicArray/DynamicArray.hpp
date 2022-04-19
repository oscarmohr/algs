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

  size_t append(T x) {
    if (_size + 1 >= _capacity)
      resize(2*_capacity);
    data[_size] = x;
    _size += 1;
  }

  void resize(size_t new_capacity) {
    auto tmp = new T[new_capacity]{0};
    _capacity = new_capacity;
    _size = std::min(_capacity, _size);
    std::copy_n(data, _size, tmp);
    delete[] data;
    data = tmp;
  }

  DynamicArray(size_t capacity=32) : _capacity{std::max(capacity, 32UZ)} {
    data = new T[capacity]{0};
  }
};
