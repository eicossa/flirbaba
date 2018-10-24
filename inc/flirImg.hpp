#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

#include "thermalMetadata.hpp"

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

  // metadata values
  double             planckr1;
  double             planckr2;
  double             planckb;
  double             planckf;
  double             plancko;
  double             tref;
  double             emis;
  double             rawvaluerange;
  double             rawvaluemedian;

  // metadata reading functions
  double readPlanckR1();
  double readPlanckR2();
  double readPlanckB();
  double readPlanckF();
  double readPlanckO();
  double readTref();
  double readEmis();
  double readRAWvaluerange();
  double readRAWvaluemedian();

  // metadata checking functions
  void               checkPlancks();
  void               checkTref();
  void               checkEmis();
  void               checkRAWvaluerange();
  void               checkRAWvaluemedian();

  int                readImageWidth();
  int                readImageHeight();
  int                readRAWThermalImageWidth();
  int                readRAWThermalImageHeight();

  // calculated values
  double             rawmin;
  double             rawmax;
  double             rawrefl;
  double             rawminobj;
  double             rawmaxobj;
  double             tmin;
  double             tmax;
  double             smin;
  double             smax;
  double             sdelta;

  int                imagewidth;
  int                imageheight;
  int                rawthermalimagewidth;
  int                rawthermalimageheight;
  
  // calculation functions
  void               calcRAWmax();
  void               calcRAWmin();
  void               calcRAWrefl();
  void               calcRAWminobj();
  void               calcRAWmaxobj();
  void               calcTmin();
  void               calcTmax();
  void               calcSmin();
  void               calcSmax();
  void               calcSdelta();

  // calculation check functions
  void               checkRAWmin();
  void               checkRAWmax();
  void               checkRAWrefl();
  void               checkRAWminobj();
  void               checkRAWmaxobj();
  void               checkTmin();
  void               checkTmax();
  void               checkSmin();
  void               checkSmax();
  void               checkSdelta();
  
public:
  flirImg();

  void               readMetadata();
  
  double getExiftoolTagInfo(std::string);
  double getPlanckR1()        {checkPlancks();              return planckr1;}
  double getPlanckR2()        {checkPlancks();              return planckr2;}
  double getPlanckB()         {checkPlancks();               return planckb;}
  double getPlanckF()         {checkPlancks();               return planckf;}
  double getPlanckO()         {checkPlancks();               return plancko;}
  double getTref()            {checkTref();                     return tref;}
  double getEmis()            {checkEmis();                     return emis;}
  double getRAWvaluerange()   {checkRAWvaluerange();   return rawvaluerange;}
  double getRAWvaluemedian()  {checkRAWvaluemedian(); return rawvaluemedian;}

  int    getImageWidth()      {return imagewidth;}
  int    getImageHeight()     {return imageheight;}
  int    getRAWThermalImageWidth()  { return rawthermalimagewidth;}
  int    getRAWThermalImageHeight() { return rawthermalimageheight;}

  void               calcEverything();

  double getRAWmax()          {checkRAWmax();                 return rawmax;}
  double getRAWmin()          {checkRAWmin();                 return rawmin;}
  double getRAWrefl()         {checkRAWrefl();               return rawrefl;}
  double getRAWmaxobj()       {checkRAWmaxobj();           return rawmaxobj;}
  double getRAWminobj()       {checkRAWminobj();           return rawminobj;}
  double getTmin()            {checkTmin();                     return tmin;}
  double getTmax()            {checkTmax();                     return tmax;}
  double getSmin()            {checkSmin();                     return smin;}
  double getSmax()            {checkSmax();                     return smax;}
  double getSdelta()          {checkSdelta();                 return sdelta;}
  
  double             calcTemp(double);
  
  std::string convert2GrayscaleCmdString();
  std::string convert2Grayscale16bitCmdString();
  std::string convert2GrayscaleMSBCmdString();
  std::string convert2GrayscaleAutolevelledCmdString();
  std::string convertThermal2Grayscale16MSBAutolevelCmdString();
  std::string resizeImageCmdString();
  
  std::string extractThermalCmdString();
  
  std::string getRGBimgpath();
  std::string getTHERMimgpath();
  std::string getTHERMimgDiagnosticpath();
  std::string getPHPimgpath();
  
  std::string getRGBimgErrorMsg();
  std::string getThermalimgErrorMsg();
  std::string getPHPimgErrorMsg();


  void    extractRawThermaldata();

  void    readRGBImage();
  void    readThermalImage();
  void    writeThermalImageAsDiagnostic();
  void    readPHPImage();

  Mat     getThermImgMat() {return thermimg;}
  Mat     getOpencvImgMat() {return opencvimg;}

  void    printMetadata();
  void    printImageSummary();
  void    printExifThermalTags();
  void    calcRaws();
  void    printMaxMinTemps();
  void    printSes();

  void    displayTooltippedImage();
};


