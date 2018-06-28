#include <string>
#include <iostream>
#include "../inc/calcStuff.hpp"
#include "../inc/getPaths.hpp"
#include "../inc/getErrmsg.hpp"
#include "../inc/flirImg.hpp"
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

void flirImg::readRGBImage()
{
    // read image from file 
    opencvimg = imread(getRGBimgpath());
 
    // if fail to read the image
    if ( opencvimg.empty() ) { 
      cout << getRGBimgErrorMsg() << getRGBimgpath() << endl;
      exit;
    } else{
      cout << "Successfully read in "
	   << getRGBimgpath() << endl;
    }
    
    //return opencvimg;
}

void flirImg::readThermalImage()
{
    // read image from file 
    thermimg = imread(getTHERMimgpath());
 
    // if fail to read the image
    if ( thermimg.empty() ) { 
      cout << getThermalimgErrorMsg() << getTHERMimgpath() << endl;
      exit;
    } else{
      cout << "Successfully read in "
	   << getTHERMimgpath() << endl;
    }
    
    //return thermimg;
}




//void extractThermalImage()
//{
//  
//}



//void readImageIntoWindow()
//{
  //namedWindow("AJRthermal", 1);
  //imshow("AJRthermal", readRGBImage());

//}

//void readExifTags()
//{
  //exifTagdata exifTagValues;
  //readExiftoolMetadata(rgbimgpath, exifTagValues);

//}



//void loadThermalData()
//{
  // read in the extracted thermal image bruh
  //readImage(thermdataimgpath.c_str(),
  //    thermalimg,
  //	    "problem loading thermal image");
//}
