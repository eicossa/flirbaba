#include <string>
#include "../inc/flirImg.hpp"
using namespace std;

std::string flirImg::getRGBimgpath()
{
  std::string path = "/home/eicossa/Dropbox/nabtd-images/FLIR1097/FLIR1097.jpg";
  return path;
}

std::string flirImg::getTHERMimgpath()
{
  std::string path = getRGBimgpath() + ".thermout.png";
  return path;
}

std::string flirImg::getPHPimgpath()
{
  std::string path = "/home/eicossa/Dropbox/wtcd/flirbaba/ir.png";
  return path;
}

