#include "thermalMetadata.hpp"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

class suitcase{

public:
  Mat             img;
  const char*     imgpath;
  Mat             thermalimg;
  const char*     rawthermdataimgpath;
  //thermalMetadata tdata;

  //suitcase(Mat &img, const char* imgpath,
  //Mat &thermalimg, const char* rawthermdataimgpath,
  //	  thermalMetadata tdata)
  //{
  //  this->img = img;
  //  this->imgpath = imgpath;
  //  this->thermalimg = thermalimg;
  //  this->rawthermdataimgpath = rawthermdataimgpath;
  //  this->tdata = tdata;
  // }
};
