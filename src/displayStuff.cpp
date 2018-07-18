#include "../inc/flirImg.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "../inc/drawingCallbacks.hpp"

using namespace std;
using namespace cv;

static void displayImageWithTempsOnMouseover()
{

}

static void displayImageWithRAWOnMouseover()
{


}

static void displayImageWithCompleteCalcsOnMouseover()
{


}

void flirImg::displayTooltippedImage()
{
  //namedWindow("RGB",     1);
  namedWindow("ThermalRectangle", 1);
  namedWindow("ThermalPolyline", 1);
  //namedWindow("PHPwaala", 1);

  //imshow("RGB",     this->opencvimg);
  imshow("ThermalRectangle", this->thermimg);
  imshow("ThermalPolyline", this->thermimg);
  //imshow("PHPwaala", this->phpimg);
  
  // set the callback function for any mouse event
  setMouseCallback("ThermalRectangle", drawSelectionRectangle, this);
  setMouseCallback("ThermalPolyline",  drawSelectionPolyline,  this);
 
  // wait until user press some key
  waitKey(0);
}
