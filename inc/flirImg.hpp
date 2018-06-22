#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

#include "thermalMetadata.hpp"

class flirImg{
  //  imgExifNormalTags  ntags;
  imgExifThermalTags ttags;
  
  imgRawData         rdata;
  imgTempData        tdata;
  //  imgSData           sdata;

  Mat                opencvimg;

};
