#ifndef FLIRIMG_H_
#define FLIRIMG_H_
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "../inc/flirImgMetadata.hpp"
#include "../inc/ErrMsgs.hpp"

using namespace std;
using namespace cv;

class flirImg{
  flirImgMetadata*    fmd;
  ErrMsgs*            emsgs;
  std::string         imgpath;
  std::string         thermal_imgpath;

  Mat                thermimg;
  Mat                temperatures;

  static void  temperatureCallBackFunc(int, int, int, int, void*);

  //static Point p2;
  //static Mat rect_thermimage_copy;
  //static bool rect_drawing;
  static void  drawSelectionRectangle(int, int, int, int, void*);
  static void  drawSelectionPolyline(int, int, int, int, void*);

public:
  flirImg();
  flirImg(std::string fimgpath);
  void printImageSummary();
  flirImgMetadata* getMetadata(){return fmd;}
  void loadRAWThermalImage();
  void displayTooltippedImage();
  
  void   calcTempForEveryPixel();

  Mat    getPixelTemperatures(){return temperatures;}
  std::string getImgPath() { return imgpath; }
  std::string getThermalImgPath() { return thermal_imgpath; }
  Mat    getThermalImgMat(){return thermimg;}
};

#endif
