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



double flirImg::getPlanckR1() { return getExiftoolTagInfo("PlanckR1"); }
double flirImg::getPlanckR2() { return getExiftoolTagInfo("PlanckR2"); }
double flirImg::getPlanckB() { return getExiftoolTagInfo("PlanckB"); }
double flirImg::getPlanckF() { return getExiftoolTagInfo("PlanckF"); }
double flirImg::getPlanckO() { return getExiftoolTagInfo("PlanckO"); }
double flirImg::getTref() { return getExiftoolTagInfo("Tref"); }
double flirImg::getEmis() { return getExiftoolTagInfo("Emis"); }
double flirImg::getRAWvaluerange() { return getExiftoolTagInfo("RAWvaluerange"); }
double flirImg::getRAWvaluemedian() { return getExiftoolTagInfo("RAWvaluemedian"); }


