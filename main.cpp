#include "inc/flirImg.hpp"
#include "inc/readImage.hpp"
#include "inc/printStuff.hpp"
#include "inc/displayStuff.hpp"

int main()
{
  flirImg img;
  img.readRGBImage();
  img.readMetadata();
  //img.calcEverything();
  //img.printImageSummary();
  //img.extractRawThermaldata();
  //img.readThermalImage();
  //img.displayTooltippedImage();
    
  return 0;
}
