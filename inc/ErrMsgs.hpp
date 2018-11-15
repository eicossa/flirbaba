#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

class ErrMsgs{
public:
  ErrMsgs()
  {
    
  }
  std::string getRGBimgErrorMsg()
  {
    std::string errmsg = "problem loading original FLIR img";
    return errmsg;
  }

  std::string getThermalImgErrorMsg()
  {
    std::string errmsg = "problem loading thermal data from img";
    return errmsg;
  }

  std::string getPHPimgErrorMsg()
  {
    std::string errmsg = "problem loading data from PHP img";
    return errmsg;
  }
};
