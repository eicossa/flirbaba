#include "../inc/flirImg.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

void draw_circle(int event, int x, int y, int flags, void* param)
{
  int            ix, iy;
  bool           drawing, mode;
  flirImg*       flirImgParam;
  Point          centre, p1, p2;
  Mat            rgbimage;

  centre.x  = x;
  centre.y  = y;
  rgbimage  = flirImgParam->getOpencvImgMat();

  
  
  if ( event == EVENT_LBUTTONDOWN ){
    drawing = true;
    p2.x      = x;
    p2.y      = y;
  }
  else if ( event == EVENT_MOUSEMOVE){
    if(drawing){
      if(mode){
	cv::rectangle(rgbimage, p2, p1, (0,255,0), -1);
      }
      else{
	cv::circle(rgbimage, centre, 5, (0,0,255), -1);
      }
    }
  }
  else if ( event == EVENT_LBUTTONUP ){
    drawing = false;
    if(mode){
      cv::rectangle(rgbimage, p2, p1, (0,255,0), -1);
    }
    else{
      cv::circle(rgbimage, centre, (0,0,255), -1);
    }
  }
  
}
