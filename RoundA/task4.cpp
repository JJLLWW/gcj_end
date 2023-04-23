#include <cstdint>
#include <iostream>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// int 1 <= N <= 10^12 < 2^63, Nth printed character of program.
// for i = 1 to 1e100:
//  for letter = A to Z: (26)
//    print letter i times

// iteration i prints 26*i characters, if iterations 1 <= k <= i all FINISHED,
// 26*(1 + 2 + ... + i) = 13i(i+1) chars printed.
// using this can get which iteration the Nth character is printed on?
// 13i(i+1) < N <= 13(i+1)(i+2) means N printed on iteration i+1.

// linear search should be fast enough to get i.

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      char c{solve()};
      std::cout << "Case #" << t << ": " << c << std::endl;
    }
  }

private:
  void read() { std::cin >> N; }
  char solve() {
    int64_t i = 1;
    for (; 13 * i * (i + 1) < N; ++i) {
      ;
    }
    int64_t offset = N - 13 * (i - 1) * i - 1;
    int char_off = static_cast<int>(offset / i);
    return 'A' + char_off;
  }

private:
  int T;
  int64_t N;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
