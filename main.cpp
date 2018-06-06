#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "inc/ExifTool.h"
#include "inc/thermalMetadata.h"
#include "inc/suitcase.h"
#include "inc/utilfunc.h"

using namespace std;
using namespace cv;

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

void calcMaxMins()
{
  // separate out the raw thermal data from the FLIR image
  extractRawThermaldata(rgbimgpath, thermdataimgpath);


  // perform calculations on thermal metadata bruh
  thermalMetadataValues.calculateRaws();
  thermalMetadataValues.calculateMaxMinTemperatures();
  thermalMetadataValues.printConsts();
  thermalMetadataValues.printRaws();
  thermalMetadataValues.printMaxMinTemps();
}

void loadThermalData()
{
  // read in the extracted thermal image bruh
  readImage(thermdataimgpath.c_str(),
	    thermalimg,
	    "problem loading thermal image");
}

void displayTooltippedImage()
{
  suitcase imgnpathdata(rgbimg, rgbimgpath,
			thermalimg, thermdataimgpath.c_str(),
			thermalMetadataValues);
  
  
  
  // set the callback function for any mouse event
  setMouseCallback("AJRthermal", CallBackFunc, &imgnpathdata);
 
  // wait until user press some key
  waitKey(0);
}

int main()
{
  calcMaxMins(readExifTags(readOriginalImage()));
  displayTooltippedImage(loadThermalData(extractThermalImage()));
    
  return 0;
}
