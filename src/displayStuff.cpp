#include "../inc/flirImg.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

static void displayImageWithTempsOnMouseover()
{

}

static void displayImageWithRAWOnMouseover()
{


}

static void displayImageWithCompleteCalcsOnMouseover()
{


}

void CallBackFunc(int event, int x, int y, int flags, void* param)
{
  double          calculatedTemp1, calculatedTemp2;
  double          thermalvalue;
  flirImg*        flirImgParam;

    // const char*     imgpath;
    // suitcase*       imgnpathdata;
    
    // thermalMetadata tdata;
    // Mat             rgb, thermalgray;

    
    if  ( event == EVENT_LBUTTONDOWN )
    {
      
      flirImgParam   = (flirImg*) param;

      //rgb          = imgnpathdata->img;
      //thermalgray  = imgnpathdata->thermalimg;
      //tdata        = imgnpathdata->tdata;
      //imgpath      = imgnpathdata->imgpath;

      Mat thermmat = flirImgParam->getThermImgMat();
      thermalvalue = (int)(thermmat).at<Vec3b>(y, x)[0];
      calculatedTemp1 = flirImgParam->calcTemp(thermalvalue);
      calculatedTemp2 = flirImgParam->calcTemp((thermalvalue*255));
	
      cout << setw(5) <<" ("<< x << ", "
    	   << y << ")  "
	   << "[ " << thermalvalue << " ]"
	   << "[ " << thermalvalue*255 << " ]"
	   << "[ Temp1 : " << calculatedTemp1 << " ]"
	   << "[ Temp2 : " << calculatedTemp2 << " ]"
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


void flirImg::displayTooltippedImage()
{
  //suitcase imgnpathdata(rgbimg, rgbimgpath,
  //			thermalimg, thermdataimgpath.c_str(),
  //	thermalMetadataValues);

  namedWindow("RGB",     1);
  namedWindow("Thermal", 1);
  namedWindow("PHPwaala", 1);

  imshow("RGB", this->opencvimg);
  imshow("Thermal", this->thermimg);
  
  
  // set the callback function for any mouse event
  setMouseCallback("Thermal", CallBackFunc, this);
 
  // wait until user press some key
  waitKey(0);
}
