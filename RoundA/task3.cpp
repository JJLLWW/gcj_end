#include <iostream>

class case_loop {
public:
    void read_and_solve() {
	std::cin >> T;
	for(int t=1; t<=T; ++t) {
	    read();
	    solve();
	    std::cout << "Case #" << t << ":";
	}
    }
private:
    void read() {
	;
    }
    void solve() {
	;
    }
private:
    int T;
};

int main() {
    case_loop main_loop;
    
}
