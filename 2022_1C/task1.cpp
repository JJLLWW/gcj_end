#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// N strings Si of letters [A-Z], bottom idx 0, top idx sz(Si)-1
// combine strings by concatenation into string S.
// can NEVER have 2 "disjoint" blocks of a character "AAABCDAA"
// - valid string S.

// clearly each Si must be valid itself, think about first and last
// chars of each Si + chars contained in each Si.

// S1 = A...B contained ACDXB, all chars != A or B must ONLY occur in
// this string. (A == B is possible). A, B the "endpts" of the string.

// call strings with 2 or more distinct chars 2-strings, without 1-strings.

// 1) If an endpt char occurs in more than 2 2-strings, IMPOSSIBLE to stack.
// 2) If an endpt char occurs in 2 2-strings, if it is the left or right endpt
// in both IMPOSSIBLE, else have X...A A...Y and potentially (A...A), unique way
// to combine.
// 3) If an endpt char occurs in a single 1-string, must be valid.

// can still run into problems A...B B...A causes loop.

// (!) cannot have ACA

// could think of "successor" (may not exist) of each string, forming a directed
// graph.

// finally need to check for cycles in the graph.

// X...A -> A...Y -> Y...B  C...D -> D...E.

// should keep track of any "parent" nodes in the graph, start gluing together
// the string from "parents", then if any strings remain there was a cycle so
// IMPOSSIBLE.

struct str_info {
  std::string str;
  char left;
  char right;
  str_info *next, *prev;
};

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
  void read() {
    std::cin >> N;
    S.resize(N);
    left_strs_of.clear(), right_strs_of.clear();
    one_strs_of.clear(), strs_of_char.clear();
    for (int i = 0; i < N; ++i) {
      std::string Si;
      std::cin >> Si;
      S[i].str = Si;
      int n = static_cast<int>(S[i].str.size());
      for (int j = 0; j < n; ++j) {
        char c = S[i].str[j];
        if (j == 0) {
          S[i].left = c;
        } else if (j == n - 1) {
          S[i].right = c;
        } else {
          strs_of_char[c].push_back(i);
        }
      }
      // keep track of if 2-string or 1-string.
      if (S[i].left == S[i].right) {
        one_strs_of[S[i].left].push_back(i);
      } else {
        left_strs_of[S[i].left].push_back(i);
        right_strs_of[S[i].right].push_back(i);
      }
    }
  }
  std::optional<std::string> solve() {
    for (char c = 'A'; c <= 'Z'; ++c) {
      // impossible if 2 strings have an interior char in common.
      if (strs_of_char[c].size() > 1) {
        return std::nullopt;
      }
      // impossible if 2 or more 2-strings have the same left or right endpoint.
      if (left_strs_of[c].size() > 1 || right_strs_of[c].size() > 1) {
        return std::nullopt;
      }
    }
    // now try and merge 2-strings, optionally inserting 1-strings in between.

    // impossible if cycle in graph.
    return std::nullopt;
  }

private:
  int T;
  int N;
  std::vector<str_info> S;
  using char_map = std::unordered_map<char, std::vector<int>>;
  char_map strs_of_char;  // strings with char as interior character
  char_map one_strs_of;   // strings A...A
  char_map left_strs_of;  // strings A...X ; X != A
  char_map right_strs_of; // strings X...A ; X != A
  std::vector<int> parents;
};

int main(int argc, char **argv) {
#ifdef DEBUG_HACK
  dh::debug_hack(argv);
#endif
  case_loop main_loop;
  main_loop.read_and_solve();
}
