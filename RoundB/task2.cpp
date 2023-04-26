#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// Size W string, chars [1-N], move takes single index and does +-N mod N.
// 0 1 2 W=3 ; 0 1 2 3 W=4 ; look at 0<=i<W/2, compare A = X[i] with B =
// X[W-1-i].

// for each pair (A, B) trying to move A and B (mod N) to a common value.
// either move A forward to B (1), or move A backward to B. (2).

// (1): A + xD = B (mod N) -> Dx = (B - A) (mod N).
// solution iff gcd(D, N) divides B - A.

// suspect test set 2 problem is overflow

struct EA_result {
  int64_t gcd;
  int64_t s;
  int64_t t;
};

// a = qb + r, 0 <= r < b, return (q, r).
std::pair<int64_t, int64_t> get_rem(int64_t a, int64_t b) {
  int q = std::floor((double)a / b);
  int r = a - q * b;
  return {q, r};
}

// gcd = s*a + t*b
EA_result extended_EA(int64_t a, int64_t b) {
  struct EA_result res;
  int64_t r_old{a}, s_old{1}, t_old{0};
  int64_t r{b}, s{0}, t{1};
  while (r != 0) {
    auto [Q, R] = get_rem(r_old, r);
    int64_t r_new{R}, s_new{s_old - Q * s}, t_new{t_old - Q * t};
    r_old = r, s_old = s, t_old = t;
    r = r_new, s = s_new, t = t_new;
  }
  res.gcd = r_old, res.s = s_old, res.t = t_old;
  return res;
}

// ax = b (mod n) solve for x.
std::optional<int64_t> solve_lcong(int64_t a, int64_t b, int64_t n) {
  EA_result ea_info{extended_EA(a, n)};
  if (b % ea_info.gcd != 0) {
    return std::nullopt;
  }
  int64_t bp{b / ea_info.gcd}, np{n / ea_info.gcd};
  auto [Q, R] = get_rem(ea_info.s * bp, np);
  return R;
}

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      std::optional<int64_t> res{solve()};
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
    std::cin >> W >> N >> D;
    X.resize(W);
    for (int i = 0; i < W; ++i) {
      std::cin >> X[i];
    }
  }
  std::optional<int64_t> solve() {
    int64_t nmove{0};
    for (int i = 0; i < W / 2; ++i) {
      int A{X[i]}, B{X[W - 1 - i]};
      std::optional<int64_t> xfor_opt{solve_lcong(D, B - A, N)},
          xback_opt{solve_lcong(D, A - B, N)};
      if (!xfor_opt.has_value() || !xback_opt.has_value()) {
        return std::nullopt;
      }
      int64_t xfor{xfor_opt.value()}, xback{xback_opt.value()};
      nmove += std::min(xfor, xback);
    }
    return nmove;
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
  case_loop main_loop;
  main_loop.read_and_solve();
}
