#include <iostream>
#include <optional>
#include <vector>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// just need O(W) solution.

// input W, N, D, size W (<= 1000) array X[i] of ints (1 <= X[i] <= N).
// min number of operations to make X[i] palindromic (or IMPOSSIBLE).

// operation moves a SINGLE wheel up or down D (with wraparound).

// odd/even W cases. 0 1 2 3 4 -> up to W/2. 0 1 2 3 -> up to W/2.

// converting to palindrome, can consider each pair independently.
// X[0], X[N-1], want x = X[0] + kD = X[N-1] + k'D.
// only possible if D divides X[N-1] - X[0].

// there's no advantage in moving A and B to a common value, so just
// move A onto B? can do this forward or backward.

// A + xD = B (mod N), A - xD = B (mod N).
// Dx + Ny = B - A, Ny - Dx = B - A.
// answer (x, y) iff gcd(D, N) divides B - A, EA to get x in both cases.

namespace {
struct EA_result {
  int gcd;
  int x;
  int y;
};
// find d = gcd(a, b) and x, y with ax + by = d.
EA_result euclidean_alg(int a, int b) {
  int r_old{a}, s_old{1}, t_old{0};
  int r{b}, s{0}, t{1};
  while (r != 0) {
    // not doing what expect.
    int r_new = r_old % r;
    int s_new = s_old % s;
    int t_new = t_old % t;
    r_old = r, r = r_new;
    s_old = s, s = s_new;
    t_old = t, t = t_new;
  }
  return {r_old, s_old, t_old};
}
} // namespace

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      std::optional<int> nops{solve()};
      std::cout << "Case #" << t << ": " << std::endl;
      if (nops.has_value()) {
        std::cout << nops.value() << std::endl;
      } else {
        std::cout << "IMPOSSIBLE" << std::endl;
      }
    }
  }

private:
  void read() {
    std::cin >> W >> N >> D;
    X.resize(W);
    for (int i = 0; i < W; ++i) {
      std::cin >> X[i];
      --X[i];
    }
  }
  std::optional<int> solve() {
    int nops{0};
    for (int i = 0; i < W / 2; ++i) {
      int A{X[i]}, B{X[W - 1 - i]};
      int gcd, a, b;
      // horrible interface
      euclidean_alg(gcd, a, b);
      if ((B - A) % gcd != 0) {
        return std::nullopt;
      }
    }
    return std::nullopt;
  }
  void euclidean_alg(int &gcd, int &a, int &b) {
    return;
    return;
  }

private:
  int T;
  int W, N, D;
  std::vector<int> X;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  EA_result res{euclidean_alg(8, 6)};
  // integer division rounds TOWARDS 0.
  std::cout << (-1) / 2 << std::endl;
  std::cout << res.gcd << " " << res.x << " " << res.y << std::endl;
}
