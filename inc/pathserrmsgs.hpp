#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

class PathsErrmsgs{
  std::string getRGBimgpath()
  {
    std::string path = "/home/eicossa/Dropbox/dset/nabtd-images/FLIR1097/FLIR1097.jpg";
    return path;
  }
  
  std::string getTHERMimgpath()
  {
    std::string path = getRGBimgpath() + ".thermout.png";
    return path;
  }
  
  std::string getTHERMimgDiagnosticpath()
  {
    std::string path = getRGBimgpath() + ".thermout.diagnostic.png";
    return path;
  }
  
  std::string getPHPimgpath()
  {
    std::string path = "/home/eicossa/Dropbox/wtcd/flirbaba/ir.png";
    return path;
  }
  
  std::string getRGBimgErrorMsg()
  {
    std::string errmsg = "problem loading original FLIR img";
    return errmsg;
  }

  std::string getThermalimgErrorMsg()
  {
    std::string errmsg = "problem loading thermal data from img";
    return errmsg;
  }

  std::string getPHPimgErrorMsg()
  {
    std::string errmsg = "problem loading data from PHP img";
    return errmsg;
  }

  std::string extractThermalCmdString();
};
