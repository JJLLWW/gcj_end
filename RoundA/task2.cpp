#include <iostream>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      solve();
      std::cout << "Case #" << t << ":";
    }
  }

private:
  void read() { ; }
  void solve() { ; }

private:
  int T;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
