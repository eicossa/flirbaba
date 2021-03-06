#include <iostream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include "../inc/getPaths.hpp"
#include "../inc/flirImg.hpp"
//#include "../inc/utilfunc.hpp"
#include "../inc/ExifTool.h"

using namespace std;
using namespace cv;

std::string flirImg::convert2GrayscaleCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - grayscale: ");
  return cmdString;
}

std::string flirImg::convert2Grayscale16bitCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - -depth 16 -endian msb -auto-level -colorspace gray ")
              + std::string(" -size ")
              + std::to_string(getRAWThermalImageWidth())
              + std::string("x")
              + std::to_string(getRAWThermalImageHeight())
              + std::string(" ");
  return cmdString;
}





std::string flirImg::resizeImageCmdString()
{
  std::string cmdString;
  return cmdString;

}

// std::string flirImg::convert2GrayscaleMSBCmdString()
// {
//   std::string cmdString;
//   cmdString = std::string("convert - -endian msb grayscale:- ");
//   return cmdString;
// }

// std::string flirImg::convert2GrayscaleAutolevelledCmdString()
// {
//   std::string cmdString;
//   cmdString = std::string("convert - -auto-level grayscale:- ");
//   return cmdString; 
// }

// std::string flirImg::convertThermal2Grayscale16MSBAutolevelCmdString()
// {
//   std::string cmdString;
//   cmdString = this->convert2GrayscaleCmdString()
//             + std::string(" | ")
//             + this->convert2Grayscale16bitCmdString()
//             + std::string(" | ")
//             + this->convert2GrayscaleMSBCmdString()
//             + std::string(" | ")
//             + this->convert2GrayscaleAutolevelledCmdString();
//   return cmdString;
// }


std::string flirImg::extractThermalCmdString()
{
  std::string cmdString;
  cmdString = std::string("exiftool ")
              + getRGBimgpath()
              + std::string(" -rawthermalimage -b ");
  return cmdString;
}
