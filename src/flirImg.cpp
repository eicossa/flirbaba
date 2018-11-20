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


void flirImg::displayRectangleSelection()
{
  namedWindow("Rectangle",   1);
  imshow("Rectangle",   this->thermimg);
  setMouseCallback("Rectangle", flirImg::drawSelectionRectangle, this);

  waitKey(0);
}


void flirImg::displayPolylineWindow(Mat img)
{
  imshow("Polyline", img);
}

void flirImg::displayPolylineSelection()
{
  namedWindow("Polyline",    1);
  flirImg::displayPolylineWindow(this->thermimg);
  //imshow("Polyline",    this->thermimg);
  setMouseCallback("Polyline",  flirImg::drawSelectionPolyline, this);

  waitKey(0);
}



void flirImg::displayBezierSelection()
{
  namedWindow("Bezier", 1);
  imshow("Bezier", this->thermimg);
  setMouseCallback("Bezier", flirImg::drawSelectionBezierCurve,    this);

  waitKey(0);
}

void flirImg::displayTooltippedImage()
{
  namedWindow("ThermalRAWimage", 1);
  imshow("ThermalRAWimage",  this->thermimg);
  setMouseCallback("ThermalRAWimage", flirImg::temperatureCallBackFunc, this);

  // wait until user press some key
  waitKey(0);
}

