#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// N <= 10^5. O(N) or O(NlogN).
// sum(Ki) <= 2*10^5 so reasonable storage.

// [choose lines to be 0-indexed]
// N stations (1 indexed), L train lines serving multiple distinct stations.
// initially all stations are connected together.
// get which stations a line starts and stops at (can convert lines to edges).

// figure out which lines cause the graph to become disconnected if remove all
// edges in the line.

// if can work out which edges are essential, can then see which lines they
// belong to. (nasty as can have multiple edges).

// if there is a multiple edge, guaranteed to be from 2 different lines so kind
// of irrelevant. Just store the line of all non-multiple edges in a hash map.

// trying to count number of essential lines.

// i < j restriction.
// line_of[i][j] = l or line_of[i][j] = NONE (if multiple edge). UNSET = -1

// do standard algo to find the bridges of the graph, then for each bridge {i,
// j} look at which line it is in and store seen lines in a std::unordered_set;

class case_loop {
private:
  template <typename T> using adjlist = std::vector<std::vector<T>>;

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
  // segfaults
  void read() {
    std::cin >> N >> L;
    lines_of.clear();
    lines_of.resize(N);
    for (int i = 0; i < N; ++i) {
      lines_of[i].resize(N);
      std::fill(lines_of[i].begin(), lines_of[i].end(), UNSET);
    }
    std::vector<int> S;
    for (int l = 0; l < L; ++l) {
      int Ki;
      std::cin >> Ki;
      S.resize(Ki);
      for (int i = 0; i < Ki; ++i) {
        std::cin >> S[i];
        --S[i]; // 1 based to 0 based conversion.
      }
      for (int i = 1; i < Ki; ++i) {
        adj[S[i]].push_back(S[i - 1]);
        adj[S[i - 1]].push_back(S[i]);
        if (lines_of[S[i]][S[i - 1]] != UNSET) {
          lines_of[S[i]][S[i - 1]] = lines_of[S[i - 1]][S[i]] = l;
        } else {
          lines_of[S[i]][S[i - 1]] = lines_of[S[i - 1]][S[i]] = NONE;
        }
      }
    }
  }
  void solve() { ; }

private:
  static constexpr int UNSET = -1, NONE = -2;
  int T;
  int N, L;
  adjlist<int> adj, lines_of;
  std::unordered_set<int> essential;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
