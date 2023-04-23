#include <string>
#include <filesystem>

// vscode can't seem to debug an executable reading from a file on mac without
// this hackery.
namespace dh {
    std::string get_filename_hack(char **argv) {
        namespace fs = std::filesystem;
        fs::path progpath(argv[0]);
        std::string exename = progpath.filename().string();
        // assume cwd is the same as the source file
        std::string txtfile = exename + ".txt";
        return txtfile.c_str();
    }
    void debug_hack(char **argv) {
        std::string txtfile {get_filename_hack(argv)};
        freopen(txtfile.c_str(), "r", stdin);
    }
}