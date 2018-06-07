void displayImageWithTempsOnMouseover()
{

}

void displayImageWithRAWOnMouseover()
{


}

void displayImageWithCompleteCalcsOnMouseover()
{


}


void displayTooltippedImage()
{
  suitcase imgnpathdata(rgbimg, rgbimgpath,
			thermalimg, thermdataimgpath.c_str(),
			thermalMetadataValues);
  
  
  
  // set the callback function for any mouse event
  setMouseCallback("AJRthermal", CallBackFunc, &imgnpathdata);
 
  // wait until user press some key
  waitKey(0);
}
