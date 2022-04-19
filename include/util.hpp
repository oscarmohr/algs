#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <istream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <numeric>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <functional>
#include <tuple>
#include <set>
#include <stack>
#include <cmath>
#include <climits>
#include <bit>
#include <cassert>
#include <tuple>
/* #include <ranges> */

namespace util {

////////////////////////////////////////////////////////////
// types and names
////////////////////////////////////////////////////////////

using u8  =  uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8  =   int8_t;
using i32 =  int32_t;
using i64 =  int64_t;

using std::tuple;
using std::vector;
using std::string;
using std::map;
using std::pair;
using std::function;
using std::cin;
using std::cout;
using std::cerr;
using std::iostream;
using std::istream;
using std::ostream;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
using std::bitset;
using std::endl;
using std::iota;
using std::reverse;
using std::min;
using std::max;
using std::abs;
using std::initializer_list;
using std::set;
using std::stack;
using std::swap;
using std::atoi;
using std::to_string;
using std::tie;

////////////////////////////////////////////////////////////
// Input/Output
////////////////////////////////////////////////////////////

#define LOG(X...) out(cerr, "\e[91m", "[LOG]: ", __func__, ":", __LINE__, " [", #X, "] = [", X, "\e[39m", '\n');
#define die_if(X) if (X) die("[die_if [" #X "]]");
#define LOOP(N) for (auto i = 1; i <= N; i++)

auto all(const auto&... args) {
  return sizeof...(args) && (... && args);
}

auto any(const auto&... args) {
  return sizeof...(args) && (... || args);
}

auto combine(const auto&... args) {
  return sizeof...(args) && (... | args);
}

auto is_in(const auto& x, const auto&... args) {
  return sizeof...(args) && (... || (x == args));
}

auto&& out(auto&& os, const auto&... args) {
  (os << ... << args); return os;
}

auto put(const auto&... args) {
  out(cout, args...);
}

auto print(const auto&... args) {
  put(args..., '\n');
}

auto str(const auto&... args) {
  return out(stringstream(), args...).str();
}

auto repeat(auto n, auto f) {
  for (auto i = 0; i < n; i++) f();
}

auto put_container(const auto& c, string s="") {
  if (c.empty()) {
    put("( )");
    return;
  }
  using std::next;
  put(s, "(");
  auto it = begin(c);
  for (; next(it) != end(c); it++)
    put(*it, ", ");
  put(*it, ")");
}

auto print_container(const auto& c, string s="") {
  put_container(c, s);
  print();
}

auto& each(auto& c, auto f) {
  for_each(c.begin(), c.end(), f);
  return c;
}

auto _getline(istream& is) {
  string line;
  std::getline(is, line);
  return line;
}

auto _getline() {
  return _getline(cin);
}

template <typename T=string>
auto get(istream& is=std::cin) {
  auto t = T();
  is >> t;
  return t;
}

template <typename T=string>
auto get_vec(istream& is=std::cin) {
  auto v = vector<T>();
  for (T t; is >> t;)
    v.push_back(t);
  return v;
}

template <typename T=string>
auto get_vec(auto n, istream& is=std::cin) {
  auto v = vector<T>();
  v.reserve(n);
  for (auto i = 0; i < n; i++)
    v.push_back(get<T>(is));
  return v;
}

template <typename T=string>
auto get_vec_n(auto n, istream& is=std::cin) {
  auto v = vector<T>();
  v.reserve(n);
  for (auto i = 0; i < n; i++)
    v.push_back(get<T>(is));
  return v;
}

auto input(const auto& s) {
  put(s);
  cin >> s;
  return s;
}

auto die(const auto&... args) {
  if (sizeof...(args))
    print(args...);
  exit(EXIT_FAILURE);
}

// clear terminal screen
void clear() {
  put("\x1b[2J",  "\x1b[H");
}

auto find(const auto& c, const auto& x) {
  return std::find(begin(c), end(c), x) != end(c);
}

auto contains(auto& c, auto& x) {
  return find(c, x);
}

auto unique(auto v) {
  auto s = set(begin(v), end(v));
  return decltype(v)(begin(s), end(s));
}

////////////////////////////////////////////////////////////
// arguments
////////////////////////////////////////////////////////////

auto get_args(int c,char **v){return vector<string>(v,v+c);}

////////////////////////////////////////////////////////////
// math
////////////////////////////////////////////////////////////

namespace math {

auto clamp(auto& x, auto min, auto max) {
  if (x < min) return x = min;
  if (x > max) return x = max;
  return x;
}

auto clamp01(auto& x){
  return clamp(x,0,1);
}

auto clamp_pm(auto& x, auto pm) {
  return clamp(x, -pm, pm);
}

auto clamp_pm1(auto& x) {
  return clamp_pm(x, 1);
}

auto clamp0(auto& x, auto max) {
  return clamp(x, 0, max);
}

/* auto randrange(auto l, auto r) { */

/* } */

} // namespace math

auto yes(auto x) { return x ? "yes" : "no"; }

template<typename T, typename TIter = decltype(std::begin(std::declval<T>()))>
constexpr auto enumerate(T&& iterable) {
  struct iterable_wrapper {
    struct iterator {
      size_t i;
      TIter iter;
      bool operator!=(const iterator& other) const { return iter != other.iter; }
      void operator++() { ++i; ++iter; }
      auto operator*() const { return std::tie(i, *iter); }
    };
    T iterable;
    auto begin() { return iterator{0, std::begin(iterable)}; }
    auto end() { return iterator{0, std::end(iterable)}; }
  };
  return iterable_wrapper{std::forward<T>(iterable)};
}

} // namespace util

#endif // #ifndef UTIL_HPP
