#include "../inc/flirImg.hpp"
#include "../inc/callbacks.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

flirImg::flirImg()
{
  fmd     = NULL;
  imgpath = "";
  thermal_imgpath ="";
  emsgs   = new ErrMsgs();
  temperatures = NULL;
}


flirImg::flirImg(std::string imgpath)
{
  fmd = new flirImgMetadata(imgpath);
  this->imgpath = imgpath;
  this->thermal_imgpath=imgpath + std::string(".thermout.png");
}

void flirImg::printImageSummary()
{
  fmd->printImageSummary();
}

void flirImg::loadRAWThermalImage()
{
    // read image from file 
    thermimg = imread(thermal_imgpath, IMREAD_ANYDEPTH);
 
    // if fail to read the image
    if ( thermimg.empty() ) { 
      cout << emsgs->getThermalImgErrorMsg() << thermal_imgpath << endl;
      exit;
    } else{
      cout << "Successfully read in "
	   << thermal_imgpath << endl;
    }
}

void flirImg::calcTempForEveryPixel()
{
  //this->getMetadata()->checkPlancks();
  //this->getMetadata()->checkSmin();
  //this->getMetadata()->checkSdelta();

  int thermalvalue;
  double calculatedTemp;

  int rawthermalimgwidth = this->getMetadata()->getRAWThermalImageWidth();
  int rawthermalimgheight=this->getMetadata()->getRAWThermalImageHeight();

  //cout << " Width "<< rawthermalimgwidth  << endl;
  //cout << " Height"<< rawthermalimgheight << endl;
  temperatures = Mat::zeros(this->thermimg.size(), CV_64F);

  for(int i=0; i<rawthermalimgwidth; i++){
    for(int j=0; j<rawthermalimgheight; j++){
      thermalvalue = (int)((this->thermimg).at<unsigned short>(j, i));
      //cout << thermalvalue << endl;
      calculatedTemp = this->getMetadata()->calcTempForOnePixel(thermalvalue);
      temperatures.at<double>(j, i) = calculatedTemp;
      //cout << temperatures.at<double>(j, i) << endl;
    }
  }
}

void flirImg::temperatureCallBackFunc(int event, int x, int y, int flags, void* param)
{
  double          calculatedTemp;
  flirImg*        flirImgObject;
  flirImgObject = (flirImg*) param;
  Mat             pixelTemps;

  pixelTemps    = flirImgObject->getPixelTemperatures();
      
  if( event == EVENT_LBUTTONDOWN ){
    calculatedTemp = pixelTemps.at<double>(y, x);
    cout << calculatedTemp << endl;
  }
  else if  ( event == EVENT_RBUTTONDOWN )
  {
    //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    //print50PixelsDiagnostics(flirImgParam);
  }
  else if  ( event == EVENT_MBUTTONDOWN )
  {
    //cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
  }
  else if ( event == EVENT_MOUSEMOVE )
  {
    //cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    calculatedTemp = pixelTemps.at<double>(y, x);
    //cout << calculatedTemp << endl;
  }    
}


void flirImg::displayTooltippedImage()
{
  namedWindow("ThermalRAWimage", 1);
  namedWindow("ThermalRectangle",   1);
  namedWindow("ThermalPolyline",    1);
  //namedWindow("ThermalBezierCurve", 1);

  imshow("ThermalRAWimage",  this->thermimg);
  imshow("ThermalRectangle",   this->thermimg);
  imshow("ThermalPolyline",    this->thermimg);
  //imshow("ThermalBezierCurve", this->thermimg);
  
  // set the callback function for any mouse event
  setMouseCallback("ThermalRAWimage", flirImg::temperatureCallBackFunc, this);
  setMouseCallback("ThermalRectangle", flirImg::drawSelectionRectangle, this);
  setMouseCallback("ThermalPolyline",  flirImg::drawSelectionPolyline,  this);
  //setMouseCallback("ThermalBezierCurve", drawSelectionBezierCurve,    this);

  // wait until user press some key
  waitKey(0);
}

static Point p2;
static Mat   rect_thermimage_copy;
static bool  rect_drawing;

void flirImg::drawSelectionRectangle(int event, int x, int y, int flags, void* param)
{
  flirImg*       flirImgObject;
  Point          p1;
  Mat            thermimg;

  flirImgObject    = (flirImg*) param;
  thermimg         = flirImgObject->getThermalImgMat();

  Mat             pixelTemps;
  pixelTemps      = flirImgObject->getPixelTemperatures();

  if ( event == EVENT_LBUTTONDOWN ){
    rect_drawing = true;
    p2.x         = x;
    p2.y         = y;
  }
  else if ( event == EVENT_MOUSEMOVE){
    p1.x    = x;
    p1.y    = y;
    if(rect_drawing){
      rect_thermimage_copy = thermimg.clone();
      cv::rectangle(rect_thermimage_copy, p2, p1, (0,255,0), 1);
      imshow("ThermalRectangle", rect_thermimage_copy);


      //cout << " Points x coords " << p1.x << " : " << p2.x <<endl;
      //cout << " Points y coords " << p1.y << " : " << p2.y <<endl;
      //cout << " --------------- " << endl;

      int imin, imax;
      int jmin, jmax;

      imin = std::min(p1.x, p2.x);
      imax = std::max(p1.x, p2.x);

      jmin = std::min(p1.y, p2.y);
      jmax = std::max(p1.y, p2.y);

      int count = 0;
      double aggreg_temp = 0.0;
      for(int loopx=imin; loopx<=imax; loopx++){
	for(int loopy=jmin; loopy<=jmax; loopy++){
	  count++;
	  //cout << " .... adding in "<< pixelTemps.at<double>(loopy, loopx) << endl;
	  aggreg_temp += pixelTemps.at<double>(loopy, loopx);
	}
      }
      cout << "Area pixelcount : " << count << " | Avg Temp : " << (double)(aggreg_temp/(double)count) << endl;

      rect_thermimage_copy.release();
    }
  }
  else if ( event == EVENT_LBUTTONUP ){
    rect_drawing = false;
    imshow("ThermalRectangle", thermimg);
  }  
}


/***********************************************************************
* *
************************************************************************/

static Point       yet_another_p;
static Mat         polyline_thermimage_copy;
static bool        polyline_drawing;
std::vector<Point> polyline_pts;
Point              polyline_start_p;


void flirImg::drawSelectionPolyline(int event, int x, int y, int flags, void* param)
{
  flirImg*           flirImgObject;
  Mat                thermimage;
  flirImgObject    = (flirImg*) param;
  thermimage       = flirImgObject->getThermalImgMat();
  
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
      polyline_pts.push_back(polyline_start_p);
    }

  }
  // Finish the figure by connecting the last point to the first point
  else if  ( event == EVENT_MBUTTONDOWN )
  {
    //cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    if(isContourConvex(polyline_pts)){
      //cout<<"... This contour is CONVEX AF!!!"<<endl;
      // Finish up the polylines diagram 
      polyline_pts.push_back(polyline_pts.at(0));
    }
    else{
      cout<<"... This contour is NOT CONVEX !!! ..."<<endl;
      polyline_drawing = false;
      polyline_pts.clear();
      imshow("ThermalPolyline", thermimage);
      // ask user to do it again!
    }
    //

    polyline_thermimage_copy = thermimage.clone();
    Mat all_ps(polyline_pts);
    // check if atleasts points available
    cv::polylines(polyline_thermimage_copy, all_ps, false, (0,255,0), 1);


    int areaOfPolygon = contourArea(polyline_pts);

    
    cout << "Area pixelcount : " << areaOfPolygon << endl;
    Scalar color(255, 255, 255 );
    int numpts = polyline_pts.size();
    Point rook_points[1][numpts];
    for(int i=0; i<numpts; i++){
      rook_points[0][i] = polyline_pts.at(i);
    }
    const Point* ppt[1] = { rook_points[0] };
    int npts[1];
    npts[0] = numpts;
    fillPoly(polyline_thermimage_copy, ppt, npts, 1, color, 8); 

    imshow("ThermalPolyline", polyline_thermimage_copy);
    //drawContours(polylines_dst, polyline_pts, -1, color, -1, 8);
    //namedWindow("Whatevs", 1);
    //imshow("Whatevs", polylines_dst);
    //imshow("ThermalPolyline", polylines_dst);
    
    polyline_thermimage_copy.release();
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
















// // this is a diagnostic thang
// void flirImg::writeThermalImageAsDiagnostic()
// {
//     // read image from file 
//     // thermimg = imread(getTHERMimgpath(), IMREAD_ANYDEPTH);

//   try{
//     imwrite(getTHERMimgDiagnosticpath(), thermimg);
//   }
//   catch(runtime_error& ex){
//     cout << ex.what() << endl;
//   }
//   cout << "Successfully wrote out diagnostic thermal image "
//        << getTHERMimgDiagnosticpath() << endl;


// }
