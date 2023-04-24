#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// N stacks, A[i] items each, [La, Ra], [Lb, Rb]. some kind of 2 player game.
// return max score of the first player.

// stacks in interval [1, N], [La, Ra] first move player 1 choices, [Lb, Rb] for
// player 2.

// both players want to maximise their own score rather than minimise the other
// player's score. (end up being the same as total score is fixed).

// max prefix/suffix sum is 10^14, larger than int64, but probably doesn't
// occur.
// get prefix sums P[1], ..., P[N], suffix sums S[1], ..., S[N] (O(N)).
// As first move at index i.
// in case 1> scoreA = min(P[i], S[i]).
// in case 2> scoreA = P[i] or S[i] depending on the sub-case.
// in case 3> if j is the closest of Lb and Rb to i, then

// A at index i, B at index j.
// case 1> * [* A *] * : scoreA = min(P[i], S[i]).
// case 2> [A * *] : score A = P[i].
// case 3> [* * A] : score A = S[i].
// case 4> [* * B] * |* * A ; [B] * |* A : score A = S[ceil((i + j)/2)].
// case 5> A |* * [B * *] ; A * |* * B : score A = P[floor((i + j)/2)].

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      int64_t res{solve()};
      std::cout << "Case #" << t << ": " << res << std::endl;
    }
  }

private:
  void read() {
    std::cin >> N;
    A.resize(N), P.resize(N), S.resize(N);
    for (int i = 0; i < N; ++i) {
      std::cin >> A[i];
    }
    std::cin >> La >> Ra >> Lb >> Rb;
    --La, --Ra, --Lb, --Rb;
    P[0] = A[0];
    S[N - 1] = A[N - 1];
    for (int i = 1; i < N; ++i) {
      P[i] = P[i - 1] + A[i];
    }
    for (int i = N - 2; i >= 0; --i) {
      S[i] = S[i + 1] + A[i];
    }
  }
  int64_t solve() {
    int64_t maxA{0};
    for (int A = La; A <= Ra; ++A) {
      int64_t scoreA{0};
      if (Lb < A && A < Rb) {
          scoreA = std::min(P[A], S[A]);
      } else if (A == Lb) {
        scoreA = P[A];
      } else if (A == Rb) {
        scoreA = S[A];
      } else if (A > Rb) {
        int64_t idx = std::ceil((double)(Rb + A) / 2);
        scoreA = S[idx];
      } else { // A < Lb
        scoreA = P[(Lb + A) / 2];
      }
      maxA = std::max(maxA, scoreA);
    }
    return maxA;
  }

private:
  int T, N;
  int La, Lb, Ra, Rb;
  std::vector<int> A;
  std::vector<int64_t> P, S;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
