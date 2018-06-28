#include <string>
#include <iostream>
#include "../inc/calcStuff.hpp"
#include "../inc/getPaths.hpp"
#include "../inc/getErrmsg.hpp"
#include "../inc/utilfunc.hpp"
#include "../inc/flirImg.hpp"
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;


void flirImg::extractRawThermaldata()
{
  //rawthermdataimagename   = imgpath + std::string(".rawthermout.png");
  //std::string output;
  std::string fullstring;
  
  fullstring = convertThermal2Grayscale16MSBAutolevelCmdString()
               +
               getRGBimgpath();
  cout << fullstring;
  
  
  output = exec(fullstring);
  //cout << output << endl;
  //rawthermdataimgpath = rawthermdataimagename.c_str();
}
