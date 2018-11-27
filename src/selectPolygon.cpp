#include "../inc/flirImg.hpp"

/***********************************************************************
* *
************************************************************************/

static Point       polyline_start_p, yet_another_p;
static std::vector<Point> polyline_pts;


static Mat         polyline_thermimage_copy;
static Mat         resized_thermimage_copy;
static Mat         resized_nolines_thermimage_copy;
//static Mat         thermimage_copy;
static Mat         tmp;

static bool        polyline_drawing;
static bool        polyline_drawing_done;
static bool        resized_once;


void flirImg::fillUpPolygonIfNecessary()
{
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
}


int flirImg::calcAreaOfPolygon()
{
  int areaOfPolygon = contourArea(polyline_pts);
  //cout << "Area pixelcount : " << areaOfPolygon << endl;
  return areaOfPolygon;

}

double flirImg::calcAvgTempWithinPolygon(Mat pixelTemps)
{
  Rect boundRect;
  boundRect = boundingRect(Mat(polyline_pts));

  Point tl  = boundRect.tl();
  Point br  = boundRect.br();
  // cv::rectangle(polyline_thermimage_copy,
  // 		    tl,
  // 		    br,
  // 		    (0, 255, 0),
  // 		    1, 8, 0);

  //cout << " Bounding Rect pts "
  //	   << tl
  //	   << " : "
  //	   << br << endl;
  int xmin = std::min(tl.x, br.x);
  int xmax = std::max(tl.x, br.x);
  int ymin = std::min(tl.y, br.y);
  int ymax = std::max(tl.y, br.y);

  int total_insider_count = 0;
  int line_insider_count = 0;
  double aggreg_temp = 0.0;
  double avg_temp = 0.0;

  Mat all_ps(polyline_pts);
  
  for(int loopy=ymin; loopy<=ymax; loopy++){
    Point p1(xmin, loopy);
    Point p2(xmax, loopy);
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
  }

  avg_temp = (double)(aggreg_temp/(double)total_insider_count);
  
  //cout << " No of points inside the polygon : "
  //     << total_insider_count << endl;
  
  //cout << " Avg temp : "
  //     << avg_temp << endl;
  
  //cout << " No of points on the polygon : "
  //     << arcLength(polyline_pts, true)
  //     << endl;
  
  return avg_temp;
}





void flirImg::drawSelectionPolyline(int event, int x, int y, int flags, void* param)
{
  flirImg* flirImgObject = (flirImg*) param;
  Mat      thermimage    = flirImgObject->getThermalImgMat();
  //flirImgObject    = (flirImg*) param;
  //thermimage       = flirImgObject->getThermalImgMat();
  //polyline_drawing_done = false;
  Mat      pixelTemps    = flirImgObject->getPixelTemperatures();

  //cout << " ... Called again ... " << endl;
  //tmp             = thermimage;
  //thermimage_copy = thermimage;
  
  if ( event == EVENT_RBUTTONDOWN ){
    polyline_drawing = false;
    polyline_drawing_done = false;
    polyline_pts.clear();
    //imshow("Polyline", thermimage);
    displayPolylineWindow(polyline_thermimage_copy);
  }
  else if ( event == EVENT_LBUTTONDOWN ){
    if(polyline_drawing){
      yet_another_p.x   = x;
      yet_another_p.y   = y;
      polyline_pts.push_back(yet_another_p);
      if( polyline_drawing ){
	
	//polyline_thermimage_copy = thermimage.clone();
	Mat all_ps(polyline_pts);
	// check if atleasts points available
	cv::polylines(polyline_thermimage_copy, all_ps, false, (0,255,0), 1);
	//imshow("Polyline", polyline_thermimage_copy);
	displayPolylineWindow(polyline_thermimage_copy);

	//polyline_thermimage_copy.release();
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
    //cout << "Middle button of the mouse is clicked - position ("
    //     << x << ", " << y << ")" << endl;
    if(isContourConvex(polyline_pts)){
      // cout<<"... This contour is CONVEX AF!!!"<<endl;
      // Finish the figure by connecting the last point to the first point
      polyline_pts.push_back(polyline_pts.at(0));
      //polyline_thermimage_copy = thermimage.clone();
      Mat all_ps(polyline_pts);
      cv::polylines(polyline_thermimage_copy, all_ps, false, (0,255,0), 1);

      
      int areapoly = flirImg::calcAreaOfPolygon();
      //flirImg::fillUpPolygonIfNecessary();
      double avgtemp = flirImg::calcAvgTempWithinPolygon(pixelTemps);

      cout << "Avg Temp : " << avgtemp << endl;
      
      //imshow("Polyline", polyline_thermimage_copy);
      displayPolylineWindow(polyline_thermimage_copy);
      polyline_drawing_done = true;
      //polyline_thermimage_copy.release();
    }
    else{
      cout<<"... This contour is NOT CONVEX !!! ..."<<endl;
      //polyline_drawing = false;
      polyline_pts.clear();
      polyline_drawing_done = false;
      //imshow("Polyline", thermimage);
      displayPolylineWindow(thermimage);
    }

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
  else if ( event == EVENT_MOUSEWHEEL ){
    int mouseWheelDelta = getMouseWheelDelta(flags);
    if(!resized_once){
      //cout << " ... The first resize ... " << endl;
      tmp                      = thermimage.clone();
      polyline_thermimage_copy = thermimage.clone();
      resized_once             = true;
    }
    else{
      //cout << " ... Image has been resized once " << endl;
      tmp = polyline_thermimage_copy;
    }
    //tmp = thermimage_copy;
    //thermimage_copy = tmp;
    if (mouseWheelDelta > 0){
      //cout << " +ve ( " << tmp.cols - 25 <<", "<< tmp.rows - 25 << " )"<<endl;
      // resize(tmp,
      // 	     thermimage_copy,
      // 	     Size( tmp.cols - 25, tmp.rows - 25 ));
      resize(tmp,
	     polyline_thermimage_copy,
	     Size(),
	     0.99, 0.99,
	     INTER_LANCZOS4);
      cout << " +ve ( " << polyline_thermimage_copy.cols <<", "
	                << polyline_thermimage_copy.rows << " )"
	                << endl;
      tmp = polyline_thermimage_copy;
      
      // pyrDown(tmp,
      // 	      thermimage_copy,
      // 	      Size( tmp.cols/2, tmp.rows/2 ));
    }
    else{
      //cout << " -ve ( " << tmp.cols + 25 <<", "<< tmp.rows + 25 << " )"<<endl;
      // resize(tmp,
      // 	     thermimage_copy,
      // 	     Size( tmp.cols + 25, tmp.rows + 25 ));
      resize(tmp,
	     polyline_thermimage_copy,
	     Size(),
	     1.01, 1.01,
	     INTER_LANCZOS4);
      cout << " -ve ( " << polyline_thermimage_copy.cols <<", "
	                << polyline_thermimage_copy.rows << " )"
	                << endl;

      tmp = polyline_thermimage_copy;
      // pyrUp(tmp,
      // 	    thermimage_copy,
      // 	    Size( tmp.cols*2, tmp.rows*2 ));
    }
    //tmp = thermimage_copy;
    //imshow("Polyline", thermimage_copy);
    displayPolylineWindow(polyline_thermimage_copy);
  }
}
