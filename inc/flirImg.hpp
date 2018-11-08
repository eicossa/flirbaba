#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

#include "thermalMetadata.hpp"
#include "flirImgMetadata.hpp"

class flirImg{
  // imgExifNormalTags  ntags;
  imgExifThermalTags ttags;
  
  imgRawData         rdata;
  imgTempData        tdata;
  // imgSData        sdata;
  std::string        imgpath;

  Mat                thermimg;
  Mat                opencvimg;
  Mat                phpimg;

  void readBasicMetadata();
  void readThermalMetadata();
  void calcMetadata();

  void extractRawThermaldata();
  void writeThermalImageAsDiagnostic();
  void readThermalImage();

  void    readThermalImage();
  void    readPHPImage();

  Mat     getThermImgMat() {return thermimg;}
  Mat     getOpencvImgMat() {return opencvimg;}

  
public:
  flirImg();

  void               readOriginalRGBImage();
  void               readAndCalculateMetadata();
  
  void               printAllMetadata();
  void               printImageSummary();

  void               calcTempForEveryPixel();

  void               displayTooltippedImage();
};


