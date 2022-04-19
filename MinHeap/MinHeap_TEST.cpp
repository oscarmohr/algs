#include "../include/util.hpp"
#include "MinHeap.hpp"

using namespace util;

void fail(string msg="") {
  print("[ FAIL ] test failed.", msg);
}

void pass(string msg="") {
  print("[ PASSED ] test passed.", msg);
}

auto test_decreasing(auto h) {
  auto N = 1000;
  auto good = true;
  print("[ TEST ] testing decreasing values from N=", N, " to -N=", -N, ".");
  for (auto i = N; good && i >= -N; i--) {
    h.insert(i);
    if (h.min() != i) {
      good = false;
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
}
