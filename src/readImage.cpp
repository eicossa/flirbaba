#include <string>

using namespace cv;
using namespace std;

std::string getRGBimgpath()
{
  std::string path = "/home/eicossa/Dropbox/nabtd-images/FLIR1097-8/FLIR1097.jpg";
  return path;
}

std::string getTHERMimgpath()
{
  std::string path = getRGBimgpath() + ".thermout.png";
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


std::string extractThermalCmdString()
{
  std::string cmdString;
  cmdString = std::string("exiftool ")
              + getRGHimgpath()
              + std::string(" -rawthermalimage -b");
              + getTHERMimgpath();
  return cmdString;
}

Mat readRGBImage()
{
    // read image from file 
    imgmat = imread(getRGBimgpath());
 
    // if fail to read the image
    if ( imgmat.empty() ) 
    { 
      cout << getRGBimgErrorMsg() << imgpath << endl;
      exit;
    }
    return imgmat;
}

void extractThermalImage()
{
  
}

Mat readThermalImage()
{
  extractThermalImage();  
  exec(extractThermalCmdString());
}




void extractRawThermaldata(const char* imgpath, std::string &rawthermdataimagename)
{
  //rawthermdataimagename   = imgpath + std::string(".rawthermout.png");
  
  std::string output;
  output = exec(rawthermaldatacmdstring);
  cout << output << endl;
  //rawthermdataimgpath = rawthermdataimagename.c_str();
}





void readImageIntoWindow()
{
  namedWindow("AJRthermal", 1);
  imshow("AJRthermal", readRGBImage());

}

void readExifTags()
{
  exifTagdata exifTagValues;
  readExiftoolMetadata(rgbimgpath, exifTagValues);

}



void loadThermalData()
{
  // read in the extracted thermal image bruh
  readImage(thermdataimgpath.c_str(),
	    thermalimg,
	    "problem loading thermal image");
}
