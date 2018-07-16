#include "../inc/flirImg.hpp"
#include "../inc/utilfunc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

void drawRectangle(int event, int x, int y, int flags, void* param)
{
  // Point ul,br;

}

void drawPolyline(int event, int x, int y, int flags, void* param)
{
  // Point** pts
  

}
void drawCircle(int event, int x, int y, int flags, void* param)
{
  //cout << "... 1. motherfucker ";
  int            ix, iy;
  bool           drawing, mode;
  flirImg*       flirImgParam;
  Point          centre, p1, p2;
  Mat            thermimage;

  centre.x  = x;
  centre.y  = y;

  flirImgParam   = (flirImg*) param;
  thermimage     = flirImgParam->getThermImgMat();

  mode=true;
  
  if ( event == EVENT_LBUTTONDOWN ){
    drawing = true;
    p2.x      = x;
    p2.y      = y;
  }
  else if ( event == EVENT_MOUSEMOVE){
    if(drawing){
  	cv::rectangle(thermimage, p2, p1, (0,255,0), -1);
    }
  }
  else if ( event == EVENT_LBUTTONUP ){
    drawing = false;
    cv::rectangle(thermimage, p2, p1, (0,255,0), -1);
  }  
}
