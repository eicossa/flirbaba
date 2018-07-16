#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

// https://stackoverflow.com/questions/478898/
// how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
std::string exec(const std::string cmd) {
    std::array<char, 128> buffer;
    std::string result;

    const char* cmdstr = cmd.c_str();
    std::shared_ptr<FILE> pipe(popen(cmdstr, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    cout<<result;
    return result;
}
