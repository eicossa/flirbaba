//#include "inc/flirImg.hpp"
#include "inc/cmdstrings.hpp"
#include "inc/exec.hpp"

//#include "inc/readImage.hpp"
//#include "inc/printStuff.hpp"
//#include "inc/displayStuff.hpp"

int main()
{
  flirImg* fimg;
  fimg = new flirImg("/home/eicossa/Dropbox/dset/nabtd-images/FLIR1097/FLIR1097.jpg");
  fimg->printImageSummary();
  cmdStrings cmdstringer(fimg);
  std::string extractThermalImageCmdString;
  extractThermalImageCmdString = cmdstringer.getExtractThermalCmdString();
  cout << extractThermalImageCmdString << endl;
  exec(extractThermalImageCmdString);
  fimg->loadRAWThermalImage();
  fimg->calcTempForEveryPixel();

  fimg->displayPolylineSelection();
  //fimg->displayTooltippedImage();
  

    
  return 0;
}

