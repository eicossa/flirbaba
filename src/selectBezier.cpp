#include "../inc/flirImg.hpp"

/***********************************************************************
* *
************************************************************************/
static Point       bezier_another_p;
static Point       bezier_start_p;
static Mat         bezier_thermimage_copy;
static bool        bezier_drawing;
std::vector<Point> beziercurve_pts;
Bezier             b;

void flirImg::drawSelectionBezierCurve(int event, int x, int y, int flags, void* param)
{  
  flirImg*       flirImgParam;
  Mat            thermimage;
  Mat            bezierpts;
  flirImgParam    = (flirImg*) param;
  thermimage      = flirImgParam->getThermalImgMat();

  if ( event == EVENT_RBUTTONDOWN ){
    bezier_drawing = false;
    beziercurve_pts.clear();
    //imshow("ThermalBezierCurve", thermimage);
    displayBezierWindow(bezier_thermimage_copy);
  }
  else if ( event == EVENT_LBUTTONDOWN ){
    if(bezier_drawing){
      bezier_another_p.x   = x;
      bezier_another_p.y   = y;
      //bezierpts.push_back(bezier_another_p);
      beziercurve_pts.push_back(bezier_another_p);
      //cout << " Size of beziercurve_pts " << beziercurve_pts.size() << endl;


      //b.set
      cout << " ... added another point to the bezier mix" << endl;
      
      if(bezier_drawing ){
        bezier_thermimage_copy = thermimage.clone();
  	Mat all_ps(beziercurve_pts);
  	// check if atleasts points available
  	// cv::drawContours();
  	// imshow("ThermalBezierCurve", bezier_thermimage_copy);
	displayBezierWindow(bezier_thermimage_copy);
  	//bezier_thermimage_copy.release();
      }
    }
    else{
      bezier_drawing           = true;
      bezier_start_p.x         = x;
      bezier_start_p.y         = y;
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
  else if ( event == EVENT_MBUTTONDOWN ){
    b.setControlPoints(beziercurve_pts);
    std::vector<Point> bezierContour = b.calcDeCastelJauCurve();
    cout << " Got these contour points " << endl;
    for(int i = 0; i < bezierContour.size(); i++){
      Point w = bezierContour.at(i);
      cout << " ( " << w.x << ", " << w.y << " )" << endl;
    }

    std::vector<std::vector<Point>> contours;
    contours.push_back(bezierContour);
    drawContours(bezier_thermimage_copy, contours, -1, Scalar(255,255,255));
    displayBezierWindow(bezier_thermimage_copy);
    
    //b.dumpPoints();
    
    //Point p;
    //p = b.getPoint(2);
    //cout << "Point 2 " << p.x << " | " << p.y << endl;
    //p = b.getPoint(900);
    //cout << "Point 900 " << p.x << " | " << p.y << endl;
    //b.getPoint(1000);


    //Point bezier_pt = b.getPoint(3);
  }

  else if ( event == EVENT_MOUSEWHEEL ){


  }
}
