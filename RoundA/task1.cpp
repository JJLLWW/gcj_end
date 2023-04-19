#include <iostream>
#include <string>
#include <array>
#include <unordered_set>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

// [A-Z] mapped to [0-9]. case is N DISTINCT words to encode.
// D[c - 'A'] gives digit word mapped to.
// return YES if are 2 different words with same encoding.

// As words are distinct can check if the computed encoding has been seen before?
// - needs to be O(N).

// If all strings at most 10 characters may be enough memory to just store converted
// representations as strings in an unordered set.

// slight problem is always need to read all N strings.

class case_loop {
public:
	case_loop() = default;
    void read_and_solve() {
		std::cin >> T;
		for(int t=1; t<=T; ++t) {
			bool is_yes {read()};
			std::cout << "Case #" << t << ": ";
			std::cout << ((is_yes) ? "YES" : "NO") << std::endl;
		}
    }
private:
    bool read() {
		seen.clear();
		for(int i=0; i<26; ++i) {
			std::cin >> D[i];
		}
		std::cin >> N;
		std::string S;
		for(int i=0; i<N; ++i) {
			std::cin >> S;
			S = encode(S);
			if(seen.count(S) > 0) {
				// BAD - doesn't read the rest of the line.
				return true;
			}
			seen.insert(S);
		}
		return false;
	}
	std::string encode(const std::string& raw_str) {
		std::string enc_str;
		for(char c : raw_str) {
			enc_str.push_back('0' + D[c - 'A']);
		}
		return enc_str;
    }
private:
    int T;
    int N;
    std::unordered_set<std::string> seen;
    std::array<int, 26> D;
};

int main(int argc, char **argv) {
	#ifdef DEBUG_HACK
	dh::debug_hack(argv);
	#endif
    case_loop main_loop;
    main_loop.read_and_solve();
}
