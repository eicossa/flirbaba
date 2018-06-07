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

#include "inc/printStuff.h"
#include "inc/displayStuff.h"

using namespace std;
using namespace cv;




void printRawSensorCalcs()
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



int main()
{
  //calcMaxMins(readExifTags(readOriginalImage()));
  //displayTooltippedImage(loadThermalData(extractThermalImage()));
    
  return 0;
}
