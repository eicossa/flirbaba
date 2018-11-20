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


