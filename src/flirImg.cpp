#include "../inc/flirImg.hpp"
#include "../inc/callbacks.hpp"
#include <opencv2/highgui/highgui.hpp>
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
    cout << calculatedTemp << endl;
  }    
}


void flirImg::displayTooltippedImage()
{
  namedWindow("ThermalRAWimage", 1);
  //namedWindow("ThermalRectangle",   1);
  //namedWindow("ThermalPolyline",    1);
  //namedWindow("ThermalBezierCurve", 1);

  imshow("ThermalRAWimage",  this->thermimg);
  //imshow("ThermalRectangle",   this->thermimg);
  //imshow("ThermalPolyline",    this->thermimg);
  //imshow("ThermalBezierCurve", this->thermimg);
  
  // set the callback function for any mouse event
  setMouseCallback("ThermalRAWimage", flirImg::temperatureCallBackFunc, this);
  //setMouseCallback("ThermalRectangle",   drawSelectionRectangle, this);
  //setMouseCallback("ThermalPolyline",    drawSelectionPolyline,  this);
  //setMouseCallback("ThermalBezierCurve", drawSelectionBezierCurve,    this);



  // wait until user press some key
  waitKey(0);
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

