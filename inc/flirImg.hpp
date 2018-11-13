#include <iostream>
#include <cmath>
#include <string>
#include <stdio>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "../inc/flirImgMetadata.hpp"
//#include "../inc/calcStuff.hpp"
//#include "../inc/getPaths.hpp"
//#include "../inc/getErrmsg.hpp"
//#include "../inc/utilfunc.hpp"
//#include "../inc/drawingCallbacks.hpp"
//#include "../inc/calcingCallbacks.hpp"

using namespace std;
using namespace cv;

class flirImg{
  flirImgMetadata    fmd;
  std::string        imgpath;

  //Mat                thermimg;
  //Mat                opencvimg;
  //Mat                phpimg;

  //void writeThermalImageAsDiagnostic();
  //void readThermalImage();

  //void readThermalImage();
  //void readPHPImage();

  //Mat  getThermImgMat() {return thermimg;}
  //Mat  getOpencvImgMat() {return opencvimg;}
  
public:
  flirImg(std::string fimgpath);
  void printImageSummary();
  //void processTempdata();
  //void displayTooltippedImage();
  

  //void               readOriginalRGBImage();
  //void               readAndCalculateMetadata();
  //void               printAllMetadata();
  //void               printImageSummary();
  //void               calcTempForEveryPixel();
};



