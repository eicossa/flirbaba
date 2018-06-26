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
  // imgSData        sdata;
  std::string        imgpath;
  Mat                opencvimg;

public: 
  double getExiftoolTagInfo(std::string);
  double getPlanckR1();
  double getPlanckR2();
  double getPlanckB();
  double getPlanckF();
  double getPlanckO();
  double getTref();
  double getEmis();
  double getRAWvaluerange();
  double getRAWvaluemedian();

  double calcRAWmax();
  double calcRAWmin();
  double calcRAWrefl();
  double calcRAWmaxobj();
  double calcRAWminobj();
  double calcTmin();
  double calcTmax();
  double calcSmax();
  double calcSmin();
  double calcSdelta();
  double calculateTemperature(double);
    
  std::string convert2GrayscaleCmdString();
  std::string convert2Grayscale16bitCmdString();
  std::string convert2GrayscaleMSBCmdString();
  std::string convert2GrayscaleAutolevelledCmdString();
  std::string convertThermal2Grayscale16MSBAutolevelCmdString();
  std::string extractThermalCmdString();
  
  std::string getRGBimgpath();
  std::string getTHERMimgpath();
  std::string getRGBimgErrorMsg();
  std::string getThermalimgErrorMsg();


  

  void    readRGBImage();
  void    printImageSummary();
  void    printExifThermalTags();
  void    calcRaws();
  void    printMaxMinTemps();
  void    printSes();

  void    displayTooltippedImage();
};
