#include "../inc/flirImg.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "../inc/drawingCallbacks.hpp"
#include "../inc/calcingCallbacks.hpp"

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
  namedWindow("ThermalRAWimage", 1);
  namedWindow("ThermalRectangle",   1);
  namedWindow("ThermalPolyline",    1);
  namedWindow("ThermalBezierCurve", 1);

  imshow("ThermalRAWimage",  this->thermimg);
  imshow("ThermalRectangle",   this->thermimg);
  imshow("ThermalPolyline",    this->thermimg);
  imshow("ThermalBezierCurve", this->thermimg);
  
  // set the callback function for any mouse event
  setMouseCallback("ThermalRAWimage",    temperatureCallBackFunc, this);
  setMouseCallback("ThermalRectangle",   drawSelectionRectangle, this);
  setMouseCallback("ThermalPolyline",    drawSelectionPolyline,  this);
  setMouseCallback("ThermalBezierCurve", drawSelectionBezierCurve,    this);



  // wait until user press some key
  waitKey(0);
}
