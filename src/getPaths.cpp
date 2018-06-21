#include <string>
using namespace std;

std::string getRGBimgpath()
{
  std::string path = "/home/eicossa/Dropbox/nabtd-images/FLIR1097-8/FLIR1097.jpg";
  return path;
}

std::string getTHERMimgpath()
{
  std::string path = getRGBimgpath() + ".thermout.png";
  return path;
}
