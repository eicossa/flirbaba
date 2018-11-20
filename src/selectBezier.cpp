#include "../inc/flirImg.hpp"

/***********************************************************************
* *
************************************************************************/
static Point       bezier_another_p;
static Point       bezier_start_p;
static Mat         bezier_thermimage_copy;
static bool        bezier_drawing;
std::vector<Point> beziercurve_pts;

void flirImg::drawSelectionBezierCurve(int event, int x, int y, int flags, void* param)
{  
  // flirImg*       flirImgParam;
  // Mat            thermimage;
  // flirImgParam    = (flirImg*) param;
  // thermimage      = flirImgParam->getThermImgMat();

  // if ( event == EVENT_RBUTTONDOWN ){
  //   bezier_drawing = false;
  //   beziercurve_pts.clear();
  //   imshow("ThermalBezierCurve", thermimage);
  // }
  // else if ( event == EVENT_LBUTTONDOWN ){
  //   if(polyline_drawing){
  //     bezier_another_p.x   = x;
  //     bezier_another_p.y   = y;
  //     beziercurve_pts.push_back(bezier_another_p);
  //     if(bezier_drawing ){
  //       bezier_thermimage_copy = thermimage.clone();
  // 	Mat all_ps(beziercurve_pts);
  // 	// check if atleasts points available
  // 	// cv::drawContours();
  // 	imshow("ThermalBezierCurve", bezier_thermimage_copy);
  // 	bezier_thermimage_copy.release();
  //     }
  //   }
  //   else{
  //     polyline_drawing           = true;
  //     polyline_start_p.x         = x;
  //     polyline_start_p.y         = y;
  //   }

  // }
  // else if ( event == EVENT_MOUSEMOVE){
  //   //
  //   //
  // }
  // else if ( event == EVENT_LBUTTONUP ){
  //   //drawing = false;
  //   //imshow("Thermal", thermimage);
  // }
}
