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

/*************************************************************************
 *
 *
 *************************************************************************/

static Point       yet_another_p;
static Mat         polyline_thermimage_copy;
static bool        polyline_drawing;
std::vector<Point> polyline_pts;
Point              polyline_start_p;


void drawSelectionPolyline(int event, int x, int y, int flags, void* param)
{
  flirImg*           flirImgParam;
  Mat                thermimage;

  flirImgParam    = (flirImg*) param;
  thermimage      = flirImgParam->getThermImgMat();
  if ( event == EVENT_RBUTTONDOWN ){
    polyline_drawing  = true;
    polyline_start_p.x         = x;
    polyline_start_p.y         = y;
  }
  else if ( event == EVENT_LBUTTONDOWN ){
    yet_another_p.x   = x;
    yet_another_p.y   = y;
    polyline_pts.push_back(yet_another_p);
    if( polyline_drawing ){
      polyline_thermimage_copy = thermimage.clone();
      Mat all_ps(polyline_pts);
      // check if atleasts points available
      cv::polylines(polyline_thermimage_copy, all_ps, true, (0,255,0), 1);
      imshow("ThermalPolyline", polyline_thermimage_copy);
      polyline_thermimage_copy.release();
    }

  }
  else if ( event == EVENT_MOUSEMOVE){
    //
    //
  }
  else if ( event == EVENT_LBUTTONUP ){
    //drawing = false;
    //imshow("Thermal", thermimage);
  }
  else if ( event == EVENT_RBUTTONUP ){
    polyline_drawing = false;
    polyline_pts.clear();
    imshow("ThermalPolyline", thermimage);
  }
}

/*************************************************************************
 *
 *
 ************************************************************************/

static Point p2;
static Mat   rect_thermimage_copy;
static bool  rect_drawing;

void drawSelectionRectangle(int event, int x, int y, int flags, void* param)
{
  flirImg*       flirImgParam;
  Point          p1;
  Mat            thermimage;

  flirImgParam    = (flirImg*) param;
  thermimage      = flirImgParam->getThermImgMat();

  if ( event == EVENT_LBUTTONDOWN ){
    rect_drawing = true;
    p2.x         = x;
    p2.y         = y;
  }
  else if ( event == EVENT_MOUSEMOVE){
    p1.x    = x;
    p1.y    = y;
    if(rect_drawing){
      rect_thermimage_copy = thermimage.clone();
      cv::rectangle(rect_thermimage_copy, p2, p1, (0,255,0), 1);
      imshow("ThermalRectangle", rect_thermimage_copy);
      rect_thermimage_copy.release();
    }
  }
  else if ( event == EVENT_LBUTTONUP ){
    rect_drawing = false;
    imshow("ThermalRectangle", thermimage);
  }  
}
