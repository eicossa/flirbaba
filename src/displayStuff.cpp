#include "../inc/suitcase.hpp"
using namespace std;

static void displayImageWithTempsOnMouseover()
{

}

static void displayImageWithRAWOnMouseover()
{


}

static void displayImageWithCompleteCalcsOnMouseover()
{


}


void displayTooltippedImage()
{
  //suitcase imgnpathdata(rgbimg, rgbimgpath,
  //			thermalimg, thermdataimgpath.c_str(),
  //	thermalMetadataValues);
  
  
  
  // set the callback function for any mouse event
  //setMouseCallback("AJRthermal", CallBackFunc, &imgnpathdata);
 
  // wait until user press some key
  //waitKey(0);
}



void CallBackFunc(int event, int x, int y, int flags, void* param)
{
    // double          calculatedTemp;
    // double          thermalvalue;

    // const char*     imgpath;
    // suitcase*       imgnpathdata;
    
    // thermalMetadata tdata;
    // Mat             rgb, thermalgray;

    
    // if  ( event == EVENT_LBUTTONDOWN )
    // {
    //   cout << "Left button of the mouse is clicked "
    // 	   <<"- position "
    // 	   <<" ("<< x << ", "
    // 	   << y << ")"
    // 	   << endl;
    //   imgnpathdata = (suitcase*) param;

    //   rgb          = imgnpathdata->img;
    //   thermalgray  = imgnpathdata->thermalimg;
    //   tdata        = imgnpathdata->tdata;
    //   imgpath      = imgnpathdata->imgpath;

    //   thermalvalue = (int)(thermalgray).at<Vec3b>(y, x)[0];
    //   calculatedTemp = tdata.calculateTemperature(thermalvalue);

    //   printf("%d %d: %d, %d, %d : %d %d %d : ( %d degrees)\n", 
    //             x, y, 
    //             (int)(rgb).at<Vec3b>(y, x)[0], 
    //             (int)(rgb).at<Vec3b>(y, x)[1], 
    //      	(int)(rgb).at<Vec3b>(y, x)[2],
    //     	(int)(thermalgray).at<Vec3b>(y, x)[0], 
    //             (int)(thermalgray).at<Vec3b>(y, x)[1], 
    //     	(int)(thermalgray).at<Vec3b>(y, x)[2],
    //     	(int)(calculatedTemp));

	
    // }
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

