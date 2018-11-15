#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

class Paths{
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
};

