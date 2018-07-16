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
  namedWindow("Thermal", 1);
  //namedWindow("PHPwaala", 1);

  //imshow("RGB",     this->opencvimg);
  imshow("Thermal", this->thermimg);
  //imshow("PHPwaala", this->phpimg);
  
  // set the callback function for any mouse event
  setMouseCallback("Thermal", drawCircle, this);
 
  // wait until user press some key
  waitKey(0);
}
