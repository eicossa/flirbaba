#include "../inc/flirImg.hpp"

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
static bool        polyline_drawing_done;
std::vector<Point> polyline_pts;
Point              polyline_start_p;


void flirImg::drawSelectionPolyline(int event, int x, int y, int flags, void* param)
{
  flirImg*           flirImgObject;
  Mat                thermimage;
  flirImgObject    = (flirImg*) param;
  thermimage       = flirImgObject->getThermalImgMat();
  //polyline_drawing_done = false;
  Mat             pixelTemps;
  pixelTemps      = flirImgObject->getPixelTemperatures();

  
  if ( event == EVENT_RBUTTONDOWN ){
    polyline_drawing = false;
    polyline_drawing_done = false;
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

  else if  ( event == EVENT_MBUTTONDOWN )
  {
    int areaOfPolygon;
    Scalar color(255, 255, 255 );
    int numpts;
    //cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    if(isContourConvex(polyline_pts)){
      // cout<<"... This contour is CONVEX AF!!!"<<endl;
      // Finish the figure by connecting the last point to the first point
      polyline_pts.push_back(polyline_pts.at(0));
      polyline_thermimage_copy = thermimage.clone();
      Mat all_ps(polyline_pts);
      cv::polylines(polyline_thermimage_copy, all_ps, false, (0,255,0), 1);
      
      areaOfPolygon = contourArea(polyline_pts);
      cout << "Area pixelcount : " << areaOfPolygon << endl;
      
      numpts = polyline_pts.size();
      Point rook_points[1][numpts];
      
      for(int i=0; i<numpts; i++){
	rook_points[0][i] = polyline_pts.at(i);
      }
      
      const Point* ppt[1] = { rook_points[0] };
      int npts[1];
      npts[0] = numpts;

      
      fillPoly(polyline_thermimage_copy, ppt, npts, 1, color, 8); 

      
      Rect boundRect;
      boundRect = boundingRect(Mat(polyline_pts));
      Point tl  = boundRect.tl();
      Point br  = boundRect.br();
      //cout << " Bounding Rect pts "
      //	   << tl
      //	   << " : "
      //	   << br << endl;

      int xmin, xmax;
      int ymin, ymax;

      xmin = std::min(tl.x, br.x);
      xmax = std::max(tl.x, br.x);

      ymin = std::min(tl.y, br.y);
      ymax = std::max(tl.y, br.y);

      int total_insider_count = 0;
      int line_insider_count = 0;
      double aggreg_temp = 0.0;
      
      for(int loopy=ymin; loopy<=ymax; loopy++){
      	Point p1(xmin, loopy);
      	Point p2(xmax, loopy);
      	//cout << "Setting line iterator bw "
      	//     << p1 << ", " << p2 << endl;
      	LineIterator litr(polyline_thermimage_copy, p1, p2, 8);
      	line_insider_count = 0;
      	for(int i = 0; i< litr.count; i++, ++litr){
      	  Point pt = litr.pos();
      	  if (pointPolygonTest(all_ps, pt, false) > 0){
      	    line_insider_count++;
	    aggreg_temp += pixelTemps.at<double>(pt.y, pt.x);
      	  }
      	}
      	//cout << " pts on line " << loopy << " : " << line_insider_count << endl;
      	total_insider_count += line_insider_count;

      	//if (pointPolygonTest(Mat(polyline_pts), Point(loopx,loopy), false) < 0){
      	//  line_insider_count++;
      	//}
      	//
      	//cout << "Line " << loopx
      	//     << " pixel-in-poly count : " << line_insider_count << endl;
      	//line_insider_count = 0;

      	//cout << " .... adding in "<< pixelTemps.at<double>(loopy, loopx) << endl;
      	//aggreg_temp += pixelTemps.at<double>(loopy, loopx);
      }
      
      
      cout << " No of points inside the polygon : "
      	   << total_insider_count
	   << " Avg temp : "
	   << (double)(aggreg_temp/(double)total_insider_count)
	   << endl;
      cout << " No of points on the polygon : "
	   << arcLength(polyline_pts, true)
	   << endl;


      

      // cv::rectangle(polyline_thermimage_copy,
      // 		    tl,
      // 		    br,
      // 		    (0, 255, 0),
      // 		    1, 8, 0);

      
      imshow("ThermalPolyline", polyline_thermimage_copy);
      //drawContours(polylines_dst, polyline_pts, -1, color, -1, 8);
      //namedWindow("Whatevs", 1);
      //imshow("Whatevs", polylines_dst);
      //imshow("ThermalPolyline", polylines_dst);
      polyline_drawing_done = true;
      polyline_thermimage_copy.release();
    }
    else{
      cout<<"... This contour is NOT CONVEX !!! ..."<<endl;
      //polyline_drawing = false;
      polyline_pts.clear();
      polyline_drawing_done = false;
      imshow("ThermalPolyline", thermimage);
      // ask user to do it again!
    }
    //

  }

  else if ( event == EVENT_MOUSEMOVE){
    //
    //
    if(polyline_drawing_done){
      //cout << "Drawing has been performed " << endl;
      Mat all_ps(polyline_pts);
      Point pt(x, y);
      if (pointPolygonTest(all_ps, pt, false) < 0){
	//cout << "Out : (" << x << ", " << y << ") "<< endl;
      }
      else{
	//cout << "In : (" << x << ", " << y << ") "<< endl;
      }
    }
    else{
      //cout << "Drawing not yet performed " << endl;
    }
  }
  else if ( event == EVENT_LBUTTONUP ){
    //drawing = false;
    //imshow("Thermal", thermimage);
  }
}





















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









