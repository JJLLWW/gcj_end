#include <algorithm>
#include <iostream>
#include <optional>
#include <unordered_set>
#include <vector>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// N (<= 10^5) +ve ints S[i], return vector or IMPOSSIBLE. (need O(N) solution)
// figure out if it is possible to replace each S[i] with other +ve int s[i]
// such that s[0] <= s[1] <= ... <= s[N-1] and S[i] == S[j] iff s[i] == s[j].
// (need to output the unique ints in the sequence s[i]).

// There is a solution iff all cards of same S[i] occur contiguously.
// eg. 1 1 1 2 2 2 2 2 3 4 4 4 4 5 NOT 1 2 1 2

// do 1 pass to see if solution exists, store seen in a set, process "block" by
// "block"
// do 2nd pass to actually get the solution if there is one.
// believe should be able to do both.

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      auto res{solve()};
      std::cout << "Case #" << t << ":";
      if (res.has_value()) {
        for (int i : res.value()) {
          std::cout << " " << i;
        }
        std::cout << std::endl;
      } else {
        std::cout << " IMPOSSIBLE" << std::endl;
      }
    }
  }

private:
  void read() {
    std::cin >> N;
    S.resize(N);
    for (int i = 0; i < N; ++i) {
      std::cin >> S[i];
    }
  }
  std::optional<std::vector<int>> solve() {
    std::vector<int> ans;
    std::unordered_set<int> seen;
    // on a new block.
    for (auto it = S.begin(); it != S.end();
         it = std::find_if(it, S.end(),
                           [it](const int &val) { return val != *it; })) {
      if (seen.count(*it) > 0) {
        return std::nullopt;
      }
      seen.insert(*it);
      ans.push_back(*it);
    }
    return ans;
  }

private:
  int T, N;
  std::vector<int> S;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
