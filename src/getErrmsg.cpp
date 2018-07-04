#include <string>
#include "../inc/flirImg.hpp"
using namespace std;

std::string flirImg::getRGBimgErrorMsg()
{
  std::string errmsg = "problem loading original FLIR img";
  return errmsg;
}

std::string flirImg::getThermalimgErrorMsg()
{
  std::string errmsg = "problem loading thermal data from img";
  return errmsg;
}

std::string flirImg::getPHPimgErrorMsg()
{
  std::string errmsg = "problem loading data from PHP img";
  return errmsg;
}
