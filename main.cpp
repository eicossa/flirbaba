#include "inc/flirImg.hpp"
#include "inc/readImage.hpp"
#include "inc/printStuff.hpp"
#include "inc/displayStuff.hpp"

int main()
{
  flirImg img;
  img = readRGBImage();
  printImageSummary(img);
  displayTooltippedImage(img);
    
  return 0;
}
