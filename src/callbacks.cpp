



void temperatureCallBackFunc(int event, int x, int y, int flags, void* param)
{
  double          calculatedTemp, calculatedTemp1, calculatedTemp2;
  double          thermalvalue, thermalvalue1, thermalvalue2;
  flirImg*        flirImgParam;

  flirImgParam = (flirImg*) param;
  // const char*     imgpath;
  // suitcase*       imgnpathdata;
  
  // thermalMetadata tdata;
  // Mat             rgb, thermalgray;

    
  if( event == EVENT_LBUTTONDOWN ){
    //flirImgParam   = (flirImg*) param;
    Mat thermmat = flirImgParam->getThermImgMat();
    thermalvalue1 = (int)((thermmat).at<unsigned short>(y, x));
    calculatedTemp1 = flirImgParam->calcTemp(thermalvalue1);
    printPixelDiagnostics(x, y, thermalvalue1, calculatedTemp1);
  }
  else if  ( event == EVENT_RBUTTONDOWN )
  {
    //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    print50PixelsDiagnostics(flirImgParam);
  }
  else if  ( event == EVENT_MBUTTONDOWN )
  {
    //cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
  }
  else if ( event == EVENT_MOUSEMOVE )
  {
    //cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
  }    
}


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
    polyline_drawing = false;
    polyline_pts.clear();
    imshow("ThermalPolyline", thermimage);
  }
  else if ( event == EVENT_LBUTTONDOWN ){
    if(polyline_drawing){
      yet_another_p.x   = x;
      yet_another_p.y   = y;
      polyline_pts.push_back(yet_another_p);
      if( polyline_drawing ){
	polyline_thermimage_copy = thermimage.clone();
	Mat all_ps(polyline_pts);
	// check if atleasts points available
	cv::polylines(polyline_thermimage_copy, all_ps, false, (0,255,0), 1);
	imshow("ThermalPolyline", polyline_thermimage_copy);
	polyline_thermimage_copy.release();
      }
    }
    else{
      polyline_drawing  = true;
      polyline_start_p.x         = x;
      polyline_start_p.y         = y;
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

/************************************************************************
 *
 *
 ***********************************************************************/

static Point       bezier_another_p;
static Point       bezier_start_p;
static Mat         bezier_thermimage_copy;
static bool        bezier_drawing;
std::vector<Point> beziercurve_pts;

void drawSelectionBezierCurve(int event, int x, int y, int flags, void* param)
{  
  flirImg*       flirImgParam;
  Mat            thermimage;
  flirImgParam    = (flirImg*) param;
  thermimage      = flirImgParam->getThermImgMat();

  if ( event == EVENT_RBUTTONDOWN ){
    bezier_drawing = false;
    beziercurve_pts.clear();
    imshow("ThermalBezierCurve", thermimage);
  }
  else if ( event == EVENT_LBUTTONDOWN ){
    if(polyline_drawing){
      bezier_another_p.x   = x;
      bezier_another_p.y   = y;
      beziercurve_pts.push_back(bezier_another_p);
      if(bezier_drawing ){
        bezier_thermimage_copy = thermimage.clone();
	Mat all_ps(beziercurve_pts);
	// check if atleasts points available
	// cv::drawContours();
	imshow("ThermalBezierCurve", bezier_thermimage_copy);
	bezier_thermimage_copy.release();
      }
    }
    else{
      polyline_drawing           = true;
      polyline_start_p.x         = x;
      polyline_start_p.y         = y;
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


}




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

#include "../inc/flirImg.hpp"


flirImg::flirImg()
{
  planckr1 = -1;
}


// #include "../inc/utilfunc.hpp"
// using namespace std;


// // find substring (case insensitive)
// int ci_find_substr( const std::string& str1,
// 		    const std::string& str2,
// 		    const std::locale& loc)
// {
//     const_iterator it = std::search( str1.begin(), str1.end(), 
//                                      str2.begin(), str2.end(),
// 				     my_equal<typename T::value_type>(loc));
//     if ( it != str1.end() ) return it - str1.begin();
//     else return -1; // not found
// }


void temperatureCallBackFunc(int event, int x, int y, int flags, void* param);
void drawSelectionRectangle(int event, int x, int y, int flags, void* param);
void drawSelectionPolyline(int event, int x, int y, int flags, void* param);
void drawSelectionBezierCurve(int event, int x, int y, int flags, void* param);
//void drawCircle(int event, int x, int y, int flags, void* param);
