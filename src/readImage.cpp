#include <string>
#include <iostream>
#include "../inc/calcStuff.hpp"
#include "../inc/getPaths.hpp"
#include "../inc/getErrmsg.hpp"
#include "../inc/flirImg.hpp"
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;




flirImg flirImg::readRGBImage()
{
    flirImg     img;
    Mat         imgmat;
    std::string imgpath;

    imgpath = getRGBimgpath();
    // read image from file 
    imgmat = imread(imgpath);
 
    // if fail to read the image
    if ( imgmat.empty() ) { 
      cout << getRGBimgErrorMsg() << imgpath << endl;
      exit;
    } else{
      cout << "Successfully read in "
	   << getRGBimgpath() << endl;
    }
    
    img.setOpencvMat(imgmat);
    return img;
}


Mat readThermalImage()
{
  //extractThermalImage();  
  //exec(extractThermalCmdString());
}




void extractRawThermaldata(const char* imgpath, std::string &rawthermdataimagename)
{
  //rawthermdataimagename   = imgpath + std::string(".rawthermout.png");
  
  //std::string output;
  //output = exec(rawthermaldatacmdstring);
  //cout << output << endl;
  //rawthermdataimgpath = rawthermdataimagename.c_str();
}


void extractThermalImage()
{
  
}



void readImageIntoWindow()
{
  //namedWindow("AJRthermal", 1);
  //imshow("AJRthermal", readRGBImage());

}

void readExifTags()
{
  //exifTagdata exifTagValues;
  //readExiftoolMetadata(rgbimgpath, exifTagValues);

}



void loadThermalData()
{
  // read in the extracted thermal image bruh
  //readImage(thermdataimgpath.c_str(),
  //    thermalimg,
  //	    "problem loading thermal image");
}
