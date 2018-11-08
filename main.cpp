#include "inc/flirImg.hpp"
#include "inc/readImage.hpp"
#include "inc/printStuff.hpp"
#include "inc/displayStuff.hpp"

int main()
{
  flirImg img;
  // read original image into memory
  img.readRGBImage();
  // read and calculate metadata params
  img.readAndCalculateMetadata();
  // print all metadata
  img.printAllMetadata();
  img.printImageSummary();

  img.calcTempForEveryPixel();
  img.displayTooltippedImage();
    
  return 0;
}

