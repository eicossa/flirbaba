#include "../inc/suitcase.h"
using namespace std;

static void displayImageWithTempsOnMouseover()
{

}

static void displayImageWithRAWOnMouseover()
{


}

static void displayImageWithCompleteCalcsOnMouseover()
{


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
