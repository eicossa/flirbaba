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

#include <iostream>

using namespace std;
using namespace cv;

class flirImgMetadata{

  double readExiftoolTagInfo(std::string tagname);
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
  flirImgReadMetadata(std::string imgpath);

  void    printCalcedMetadata();
  void    printReadMetadata();
  void    printImageSummary();

};


