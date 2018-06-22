#include <iostream>
#include "../inc/thermalMetadata.hpp"
#include "../inc/ExifTool.h"
#include "../inc/getPaths.hpp"
#include "../inc/ExifToolPipe.h"
#include "../inc/TagInfo.h"
#include <iostream>
using namespace std;

double getExiftoolTagInfo(std::string tagname)
{
  std::string imgpath;
  imgpath = getRGBimgpath();
  // create our ExifTool objetc
  ExifTool *et = new ExifTool();
  // read metadata from the image
  TagInfo *info = et->ImageInfo(imgpath.c_str(), NULL, 5);
  
  if (info) {
    for (TagInfo *i=info; i; i=i->next) {
      if(!ci_find_substr( i->name , tagname)){
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



double getPlanckR1() { return getExiftoolTagInfo("PlanckR1"); }
double getPlanckR2() { return getExiftoolTagInfo("PlanckR2"); }
double getPlanckB() { return getExiftoolTagInfo("PlanckB"); }
double getPlanckF() { return getExiftoolTagInfo("PlanckF"); }
double getPlanckO() { return getExiftoolTagInfo("PlanckO"); }
double getTref() { return getExiftoolTagInfo("Tref"); }
double getEmis() { return getExiftoolTagInfo("Emis"); }
double getRAWvaluerange() { return getExiftoolTagInfo("RAWvaluerange"); }
double getRAWvaluemedian() { return getExiftoolTagInfo("RAWvaluemedian"); }


// void readExifTags(const char* imgpath, exifTagdata &exifTagValues)
// {
//   // to hold the exiftool tag info
//   double planckr1, planckr2;
//   double planckb, planckf, plancko;
//   double tref, emis;
//   double rawvaluemedian, rawvaluerange;

//   readTags(planckr1, planckr2, planckb, planckf, plancko,
// 	   tref, emis,
// 	   rawvaluemedian, rawvaluerange);

  

  
//   thermalMetadata tdata(planckr1, planckr2,
// 			planckb, planckf, plancko,
// 			tref, emis,
// 			rawvaluemedian, rawvaluerange);
//   thermalMetadataValues = tdata;
  
//   // print exiftool stderr messages
//   char *err = et->GetError();
//   if (err) cerr << err;
//   delete et;      // delete our ExifTool object
// }
