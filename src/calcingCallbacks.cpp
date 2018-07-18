#include <stdio.h>
#include "../inc/flirImg.hpp"
#include "../inc/calcingCallbacks.hpp"
using namespace std;


void CallBackFunc(int event, int x, int y, int flags, void* param)
{
  double          calculatedTemp1, calculatedTemp2;
  double          thermalvalue;
  flirImg*        flirImgParam;

  // const char*     imgpath;
  // suitcase*       imgnpathdata;
  
  // thermalMetadata tdata;
  // Mat             rgb, thermalgray;

    
  if  ( event == EVENT_LBUTTONDOWN ){
    flirImgParam   = (flirImg*) param;
    Mat thermmat = flirImgParam->getThermImgMat();
    thermalvalue = (int)(thermmat).at<Vec3b>(y, x)[0];
    calculatedTemp1 = flirImgParam->calcTemp(thermalvalue);
	
    cout << setw(5) <<" ("<< x << ", "
	 << y << ")  "
	 << "[ "        << thermalvalue    << " ]"
	 << "[ Temp : " << calculatedTemp1 << " ]"
	 << endl;

    //calculatedTemp = tdata.calculateTemperature(thermalvalue);

    // printf("%d %d: %d, %d, %d : %d %d %d : ( %d degrees)\n", 
    //           x, y, 
    //           (int)(rgb).at<Vec3b>(y, x)[0], 
    //           (int)(rgb).at<Vec3b>(y, x)[1], 
    //    	(int)(rgb).at<Vec3b>(y, x)[2],
    //   	(int)(thermalgray).at<Vec3b>(y, x)[0], 
    //           (int)(thermalgray).at<Vec3b>(y, x)[1], 
    //   	(int)(thermalgray).at<Vec3b>(y, x)[2],
    //   	(int)(calculatedTemp));

	
  }
  // else if  ( event == EVENT_RBUTTONDOWN )
  // {
  //   //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
  // }
  // else if  ( event == EVENT_MBUTTONDOWN )
  // {
  //   //cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
  // }
  // else if ( event == EVENT_MOUSEMOVE )
  // {
  //   //cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
  // }    
}
