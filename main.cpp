#include "inc/flirImg.hpp"
#include "inc/readImage.hpp"
#include "inc/printStuff.hpp"
#include "inc/displayStuff.hpp"

int main()
{
  flirImg fimg("/home/eicossa/Dropbox/dset/nabtd-images/FLIR1097/FLIR1097.jpg");
  fimg.printImageSummary();
  //fimg.printImageSummary();
  //fimg.processTempdata();
  //fimg.storeImageData();
  //fimg.displayTooltippedImage();

  
  // read original image into memory
  //img.readRGBImage();
  // read and calculate metadata params
  //img.readAndCalculateMetadata();
  // print all metadata
  //img.printAllMetadata();
  //img.printImageSummary();
  //img.calcTempForEveryPixel();
  //img.displayTooltippedImage();
    
  return 0;
}

