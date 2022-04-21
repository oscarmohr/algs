#include "../include/util.hpp"
#include "MinHeap.hpp"

using namespace util;

void fail(string msg="") {
  put("[ FAIL ] test failed.");
  print(msg == "" ? msg : " " + msg);
}

void pass(string msg="") {
  put("[ PASSED ] test passed.");
  print(msg == "" ? msg : " " + msg);
}

auto test_decreasing(auto h) {
  auto N = 1000;
  auto good = true;

  print("[ TEST ] testing decreasing values from N=", N, " to -N=", -N, ".");

  for (auto i = N; good && i >= -N; i--) {
    h.insert(i);
    if (h.min() != i) {
      good = false;
      fail("incorrect minimum.");
      break;
    }
  }

  good ? pass() : fail();
  return good;
}

auto test_large_cardinality(auto h) {
  auto N = 1e8;
  auto good = true;

  print("[ TEST ] testing large cardinality of ", N);

  for (auto i = 0; i < N; i++)
    h.insert(i);

  for (auto i = 0; i < N - 1; i++) {
    if (h.min() != i) {
      good = false;
      fail("incorrect minimum.");
      break;
    }
    h.pop_min();
  }

  good ? pass() : fail();
  return good;
}

auto test_array_initialization() {
  auto N = 1e4;
  auto good = true;


  print("[ TEST ] testing array initialization of ", N, " random elements");

  auto tmp = new int[N];

  for (auto i = 0; i < N; i++)
    tmp[i] = std::rand();

  auto h = MinHeap(tmp, N);

  delete[] tmp;

  auto ref = std::vector<int>();

  for (auto i = 0; i < N; i++) {
    ref.push_back(h.min());
    h.pop_min();
  }

  for (auto i = 0; i < N - 1; i++) {
    if (ref[i] > ref[i + 1]) {
      good = false;
      fail("unsorted.");
      break;
    }
  }
  
  good ? pass() : fail();
  return good;
}

auto test(auto t, const auto& args...) {
  auto good = true;
  try {
    good = t(args);
    pass();
  } catch (std::exception& e) {
    good = false;
    fail(e.what());
  }
  return good;
}

int main() {
  test_decreasing(MinHeap(50));
  test_large_cardinality(MinHeap(12));
  test_array_initialization();
}
