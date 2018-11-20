#include "../inc/flirImg.hpp"

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
