#include "inc/flirImg.h"
#include "inc/printStuff.h"
#include "inc/displayStuff.h"

int main()
{
  flirImg img;
  img = readImage();
  printImageSummary(img);
  displayTooltippedImage(img);
    
  return 0;
}
