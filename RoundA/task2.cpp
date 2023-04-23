#include <iostream>
#include <optional>
#include <vector>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// Large interval of real nums X = [0, M]. N intervals I[i] = [X[i]-R,X[i]+R].
// (is gap between [2, 4] and [5, 8]).

// Choose which lights to keep from left X[0] to right X[N-1], keep track of
// currently lit area [0, L], initially [0,0] and current chosen i (initially
// -1). Stop when L >= M.

// For j > i, either no X[j] in [L, L+R], so IMPOSSIBLE, or choose the greatest
// such X[j] (X[j+1] > L + R or j = N-1), and update L = X[j] + R.

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      std::optional<int> res{solve()};
      std::cout << "Case #" << t << ": ";
      if (res.has_value()) {
        std::cout << res.value() << std::endl;
      } else {
        std::cout << "IMPOSSIBLE" << std::endl;
      }
    }
  }

private:
  void read() {
    std::cin >> M >> R >> N;
    X.resize(N);
    for (int i = 0; i < N; ++i) {
      std::cin >> X[i];
    }
  }
  std::optional<int> solve() {
    int L{0}, i{-1}, nplaced{0};
    while (L < M) {
      int j{i + 1};
      if (j >= N || X[j] > L + R) {
        return std::nullopt;
      };
      while (j < N - 1 && X[j + 1] <= L + R) {
        ++j;
      }
      i = j;
      L = X[i] + R;
      ++nplaced;
    }
    return nplaced;
  }

private:
  int T;
  int M, R, N;
  std::vector<int> X;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
