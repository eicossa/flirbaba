#include <string>
using namespace std;

std::string getRGBimgErrorMsg()
{
  std::string errmsg = "problem loading original FLIR img";
  return errmsg;
}

std::string getThermalimgErrorMsg()
{
  std::string errmsg = "problem loading thermal data from img";
  return errmsg;
}
