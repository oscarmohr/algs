#include "../include/util.hpp"
#include "MinHeap.hpp"

using namespace util;

int main() {
  // create new MinHeap with initial capacity of 100
  auto h = MinHeap(100);

  print("inserting elements...");
  h.insert(8);
  h.insert(231);

  // efficiently get minimum value in MinHeap. min = 8
  print("min is ", h.min());

  print("inserting some more elements...");
  h.insert(16);
  h.insert(-1);

  // min is now -1
  print("min is now ", h.min());

  // remove minimal element
  print("removing minimum.");
  h.del();

  // min is back to 8 again
  print("min is now again ", h.min());

  /* auto pmin = [&]{ print("min() = ", h.min()); }; */
  /* auto pst = [&]{ */
  /*   put("size = ", h.len(), ", capacity = ", h.get_capacity(), "\n\tdata = "); */
  /*   if (auto st = h.elems(); not h.empty()) */
  /*     print_container(h.elems()); */
  /*   else */
  /*     print("( )"); */
  /* }; */

  /* pst(); */

}
