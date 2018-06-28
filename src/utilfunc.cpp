// #include "../inc/utilfunc.hpp"
// using namespace std;


// // find substring (case insensitive)
// int ci_find_substr( const std::string& str1,
// 		    const std::string& str2,
// 		    const std::locale& loc)
// {
//     const_iterator it = std::search( str1.begin(), str1.end(), 
//                                      str2.begin(), str2.end(),
// 				     my_equal<typename T::value_type>(loc));
//     if ( it != str1.end() ) return it - str1.begin();
//     else return -1; // not found
// }


// // https://stackoverflow.com/questions/478898/
// // how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
// std::string exec(const std::string cmd) {
//     std::array<char, 128> buffer;
//     std::string result;

//     const char* cmdstr = cmd.c_str();
//     std::shared_ptr<FILE> pipe(popen(cmdstr, "r"), pclose);
//     if (!pipe) throw std::runtime_error("popen() failed!");
//     while (!feof(pipe.get())) {
//         if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
//             result += buffer.data();
//     }
//     cout<<result;
//     return result;
// }
