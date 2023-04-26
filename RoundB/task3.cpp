#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// need O(N)

// size N (<= 10^5) distinct int array A, +ve int K (<= 10^9).
// return max size spacious subset A containing A[i] for each i.
// set S spacious if any pair x,y in S have |x-y| >= K.

// if didn't have to be subset of A, could just take S = {A[i] + nK}.

// given current leftmost elem l and rightmost elem r, want:
// 1) least element r' in A with r' >= r + K. (if none stop)
// 2) greatest element l' in A with l' <= l - K. (if none stop)

// sort A increasing, keep track of copy in original order for output.
// is it possible to keep track of r and l for each integer x in O(N)?

// next[i] = r, prev[i] = l, N for no value.

// calc next[0]
// loop i = 1 to N-1:
// if next[i-1] works use it, else move up.

// calc prev[N-1]
// loop i = N-2 to 0:
// if prev[i+1] works use it, else move down.

// still too slow, O(N^2) for ALL elements.

// surely if have this information, can precompute number of elements to the
// left and right of a given idx in a similar way.

// left[i] = left[next[i]] + 1.  left[NO_VAL] = 0
// right[i] = right[prev[i]] + 1. right[NO_VAL] = 0.

// in sorted list can bsearch for

struct list_node {
  list_node() = default;
  int next, prev;
  int left, right;
};

class case_loop {
public:
  case_loop() = default;
  void read_and_solve() {
    std::cin >> T;
    for (int t = 1; t <= T; ++t) {
      read();
      std::vector<int> res{solve()};
      std::cout << "Case #" << t << ":";
      for (int i = 0; i < N; ++i) {
        std::cout << " " << res[i];
      }
      std::cout << std::endl;
    }
  }

private:
  void precompute_nodes() {
    int j{0};
    for (int i = 0; i < N; ++i) {
      while (j < N && vals[j] < vals[i] + K) {
        ++j;
      }
      if (j < N && vals[j] >= vals[i] + K) {
        nodes[i].next = j;
      } else {
        nodes[i].next = N; // no next
      }
    }
    j = N - 1;
    for (int i = N - 1; i >= 0; --i) {
      while (j >= 0 && vals[j] > vals[i] - K) {
        --j;
      }
      if (j >= 0 && vals[j] <= vals[i] + K) {
        nodes[i].prev = j;
      } else {
        nodes[i].prev = N; // no prev
      }
    }
    for (int i = 0; i < N; ++i) {
      int prev = nodes[i].prev;
      if (i == 0 || prev == N) {
        nodes[i].left = 0;
      } else {
        nodes[i].left = 1 + nodes[prev].left;
      }
    }
    for (int i = N - 1; i >= 0; --i) {
      int next = nodes[i].next;
      if (i == N - 1 || next == N) {
        nodes[i].right = 0;
      } else {
        nodes[i].right = 1 + nodes[next].right;
      }
    }
  }
  void read() {
    std::cin >> N >> K;
    A.resize(N), nodes.resize(N), vals.resize(N);
    for (int i = 0; i < N; ++i) {
      std::cin >> A[i];
      vals[i] = A[i];
    }
    std::sort(vals.begin(), vals.end());
    precompute_nodes();
  }
  std::vector<int> solve() {
    std::vector<int> res(N);
    // O(NlogN)
    for (int i = 0; i < N; ++i) {
      auto it = std::lower_bound(vals.begin(), vals.end(), A[i]);
      int j = std::distance(vals.begin(), it);
      res[i] = nodes[j].left + 1 + nodes[j].right;
    }
    return res;
  }

private:
  int T;
  int N, K;
  std::vector<int> A, vals;
  std::vector<list_node> nodes;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
