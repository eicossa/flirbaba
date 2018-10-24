#include <stdio.h>
#include "../inc/flirImg.hpp"
#include "../inc/calcingCallbacks.hpp"
using namespace std;

void printPixelDiagnostics(int coord_x, int coord_y,
			   int thermalintensityvalue,
			   double calculatedTemp)
{
  cout << setw(5)
       <<" ("
       << coord_x << ", "
       << coord_y << ")  "
       << "[ "        << thermalintensityvalue    << " ]"
       << "[ Temp : " << calculatedTemp << " ]"
       << endl;
}

void print50PixelsDiagnostics(flirImg* flirImgParam)
{
  Mat thermmat = flirImgParam->getThermImgMat();
  int thermalvalue;
  double calculatedTemp;
  
  int j=24;
  for(int i=200; i<=250; i++){
    thermalvalue = (int)((thermmat).at<unsigned short>(j, i));
    //cout << thermalvalue << endl;
    calculatedTemp = flirImgParam->calcTemp(thermalvalue);
    printPixelDiagnostics(i, j, thermalvalue, calculatedTemp);
  }

}


// void printDiagnostics(int x, int y, Mat thermimg, flirImg &flirImgParam)
// {
//   int thermalvalue;
//   thermalvalue = (int)(thermimg).at<Vec3b>(y, x)[0];
//   cout << thermalvalue << endl;


//   cout << setw(5)
//        <<" ("
//        << x << ", "
//        << y << ")  "
//        << "[ "        << thermalvalue    << " ]"
//        << "[ Temp : " << calculatedTemp2 << " ]"
//        << endl;



// }

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

    //cin >> thermalvalue2;
    
    //calculatedTemp2 = flirImgParam->calcTemp(thermalvalue2);
    //cout << setw(5)
    //	 <<" ("
    //	 << x << ", "
    //	 << y << ")  "
    //	 << "[ "        << thermalvalue2    << " ]"
    //	 << "[ Temp : " << calculatedTemp2 << " ]"
    //	 << endl;


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
  else if  ( event == EVENT_RBUTTONDOWN )
  {
    //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    print50PixelsDiagnostics(flirImgParam);
  }
  // else if  ( event == EVENT_MBUTTONDOWN )
  // {
  //   //cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
  // }
  // else if ( event == EVENT_MOUSEMOVE )
  // {
  //   //cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
  // }    
}
