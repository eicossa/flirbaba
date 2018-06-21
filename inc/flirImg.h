#include <stdio>
using namespace std;

#include "imgExifThermalTags.h"
#include "imgRawData.h"
#include "imgTempData.h"
#include "imgSdata.h"

class flirImg{
  imgExifNormalTags  ntags;
  imgExifThermalTags ttags;
  
  imgRawData         rdata;
  imgTempData        tdata;
  imgSData           sdata;


};
