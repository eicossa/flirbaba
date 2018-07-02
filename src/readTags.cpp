#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

#include "../inc/ExifTool.h"
#include "../inc/utilfunc.hpp"
#include "../inc/getPaths.hpp"
#include "../inc/flirImg.hpp"

using namespace std;

double flirImg::getExiftoolTagInfo(std::string tagname)
{
  std::string imgpath;
  std::string readtaglist;
  imgpath = getRGBimgpath();
  // create our ExifTool objetc
  ExifTool *et = new ExifTool();
  // read metadata from the image
  TagInfo *info = et->ImageInfo(imgpath.c_str(), NULL, 5);
  
  if (info) {
    for (TagInfo *i=info; i; i=i->next) {
      readtaglist = std::string(i->name);
      if(!ci_find_substr( readtaglist, tagname)){
	//cout << tagname << " : " << i-> value << endl;
        return stod(i->value);
      } 
    }
    // we are responsible for deleting the information when done
    delete info;
  } else if (et->LastComplete() <= 0) {
    cerr << "Error executing exiftool!" << endl;
  }
  return 1.0f;
}



double flirImg::readPlanckR1() { return getExiftoolTagInfo("PlanckR1"); }
double flirImg::readPlanckR2() { return getExiftoolTagInfo("PlanckR2"); }
double flirImg::readPlanckB() { return getExiftoolTagInfo("PlanckB"); }
double flirImg::readPlanckF() { return getExiftoolTagInfo("PlanckF"); }
double flirImg::readPlanckO() { return getExiftoolTagInfo("PlanckO"); }
double flirImg::readTref() { return getExiftoolTagInfo("Tref"); }
double flirImg::readEmis() { return getExiftoolTagInfo("Emis"); }
double flirImg::readRAWvaluerange() { return getExiftoolTagInfo("RAWvaluerange"); }
double flirImg::readRAWvaluemedian() { return getExiftoolTagInfo("RAWvaluemedian"); }


void flirImg::readMetadata()
{
  planckr1 = readPlanckR1();
  planckr2 = readPlanckR2();
  planckb  = readPlanckB();
  planckf  = readPlanckF();
  plancko  = readPlanckO();
  tref     = readTref();
  emis     = readEmis();
  rawvaluerange = readRAWvaluerange();
  rawvaluemedian = readRAWvaluemedian();
}
