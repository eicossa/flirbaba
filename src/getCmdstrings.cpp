#include <iostream>
#include <cstdio>
#include <stdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include "../inc/getPaths.hpp"
#include "../inc/ExifTool.h"
#include "../inc/suitcase.h"
#include "../inc/utilfunc.h"

using namespace std;
using namespace cv;

std::string convert2GrayscaleCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - grayscale:- ");
  return cmdString;
}

std::string convert2Grayscale16bitCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - -depth 16 grayscale:- ");
  return cmdString;
}

std::string convert2GrayscaleMSBCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - -endian msb grayscale:- ");
  return cmdString;
}

std::string convert2GrayscaleAutolevelledCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - -auto-level grayscale:- ");
  return cmdString; 
}

std::string convertThermal2Grayscale16MSBAutolevelCmdString()
{
  std::string cmdString;
  cmdString = convert2GrayscaleCmdString()
            + std::string(" | ")
            + convert2Grayscale16bitCmdString()
            + std::string(" | ")
            + convert2GrayscaleMSBCmdString()
            + std::string(" | ")
            + convert2GrayscaleAutolevelledCmdString();
  return cmdString;
}


std::string extractThermalCmdString()
{
  std::string cmdString;
  cmdString = std::string("exiftool ")
              + getRGBimgpath()
              + std::string(" -rawthermalimage -b");
              + getTHERMimgpath();
  return cmdString;
}
