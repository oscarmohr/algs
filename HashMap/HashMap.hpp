#include <algorithm>
#include <cstddef>

template<typename KeyType=size_t, typename ValType=int>
struct HashMapEntry {
  KeyType key;
  ValType val;
};

// if your keys are not of integral type, find bijection to naturals and convert manually
template<typename T=int>
class HashMap {
private:
  using Entry = HashMapEntry<KeyType, ValType>;

  T* data;
  size_t _size;
  size_t _capacity;

public:
  HashMap() {
  }
};
