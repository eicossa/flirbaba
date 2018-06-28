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

template<typename T>
int ci_find_substr( const T&,
		    const T&,
		    const std::locale& loc = std::locale() );

std::string exec(const std::string);



