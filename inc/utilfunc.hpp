#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <algorithm>
//#include <array>

using namespace std;
#include <array>
#include <memory>

// templated version of my_equal so it could work with both char and wchar_t
template<typename charT>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
int ci_find_substr( const T& str1,
		    const T& str2,
		    const std::locale& loc = std::locale() )
{
    typename T::const_iterator it = std::search( str1.begin(), str1.end(), 
                                                 str2.begin(), str2.end(),
						 my_equal<typename T::value_type>(loc) );
    if ( it != str1.end() ) return it - str1.begin();
    else return -1; // not found
}


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
