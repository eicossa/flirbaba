#ifndef FLIRIMGMETADATA_H_
#define FLIRIMGMETADATA_H_

#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <cassert>
#include <opencv2/opencv.hpp>
#include "../inc/ExifTool.h"
#include "../inc/utilfunc.hpp"

using namespace std;
using namespace cv;

class flirImgMetadata{
  std::string imgpath;

  // read thermal metadata
  double planckr1, planckr2, planckb, planckf, plancko;
  double tref, emis;
  double rawvaluerange, rawvaluemedian;
  // read basic metadata
  int imagewidth, imageheight;
  int rawthermalimagewidth, rawthermalimageheight;
  // calculated values
  double             rawmin, rawmax, rawrefl;
  double             rawminobj, rawmaxobj;
  double             tmin, tmax;
  double             smin, smax, sdelta;

  // the workhorse image reader
  double readExiftoolTagInfo(std::string tagname);
  
  //reading methods
  void readThermalMetadata();
  void readBasicMetadata();

  // checking methods  
  void checkReadMetadata();
  void checkCalcedMetadata();

  // calculation methods
  void               calcRAWmax();
  void               calcRAWmin();
  void               calcRAWrefl();
  void               calcRAWminobj();
  void               calcRAWmaxobj();
  void               calcRaws();
  
  void               calcTmin();
  void               calcTmax();
  void               calcTs();
  
  void               calcSmin();
  void               calcSmax();
  void               calcSdelta();
  void               calcSes();

  void               readAllMetadata();
  void               calcAllMetadata();

public:
  flirImgMetadata();
  flirImgMetadata(std::string imgpath);

  double calcTempForOnePixel(double thermalintensityvalue);

  void    printCalcedMetadata();
  void    printReadMetadata();
  void    printImageSummary();

  int     getRAWThermalImageWidth(){return rawthermalimagewidth;}
  int     getRAWThermalImageHeight(){return rawthermalimageheight;}

};


#endif
