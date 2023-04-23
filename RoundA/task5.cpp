#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// get initial choices for the N people, want min number changes so no 2
// neighbours have same choice.

// size 2 block of equal elems
// PRRS -> PSRS (1 move).

// size k block of equal elems
// PRRRRS -> PRSRPS (2 move).
// PRRRRRRS -> PR*R*R*S (3 move).
// PRRRP -> PR*RP.
// believe can always get rid of a size k block with floor(k/2) moves.

// NASTY: could just have the entire ring is a size k block RRRRR.
// R*R*R* R*R*R, R*R*. Then takes ceil(k/2) moves.

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      int nmove{solve()};
      std::cout << "Case #" << t << ": " << nmove << std::endl;
    }
  }

private:
  void read() {
    std::cin >> C;
    N = static_cast<int>(C.size());
  }
  int solve() {
    int nmove{0};
    size_t first = C.find_first_not_of(C[0]);
    // edge case - entire ring is a block RRRRR
    if (first == std::string::npos) {
      return static_cast<int>(std::ceil((double)N / 2));
    }
    for (size_t i = first; i != std::string::npos;) {
      size_t j = C.find_first_not_of(C[i], i);
      // edge case - loop around for last block.
      if (j == std::string::npos) {
        if (C[0] == C[N - 1]) {
          nmove += (first + N - i) / 2;
        } else {
          nmove += first / 2 + (N - i) / 2;
        }
      } else {
        nmove += (j - i) / 2;
      }
      i = j;
    }
    return nmove;
  }

private:
  int T, N;
  std::string C;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
