#include "inc/thermalMetadata.h"

double getPlanckR1() { return getExiftoolTagInfo("PlanckR1"); }
double getPlanckR2() { return getExiftoolTagInfo("PlanckR2"); }
double getPlanckB() { return getExiftoolTagInfo("PlanckB"); }
double getPlanckF() { return getExiftoolTagInfo("PlanckF"); }
double getPlanckO() { return getExiftoolTagInfo("PlanckO"); }
double getTref() { return getExiftoolTagInfo("Tref"); }
double getEmis() { return getExiftoolTagInfo("Emis"); }
double getRAWvaluerange() { return getExiftoolTagInfo("RAWvaluerange"); }
double getRAWvaluemedian() { return getExiftoolTagInfo("RAWvaluemedian"); }

void getExiftoolTagInfo(std::string tagname)
{
  // create our ExifTool objetc
  ExifTool *et = new ExifTool();
  // read metadata from the image
  TagInfo *info = et->ImageInfo(imgpath, NULL, 5);
  
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

}

void readExifTags(const char* imgpath, exifTagdata &exifTagValues)
{
  // to hold the exiftool tag info
  double planckr1, planckr2;
  double planckb, planckf, plancko;
  double tref, emis;
  double rawvaluemedian, rawvaluerange;

  readTags(planckr1, planckr2, planckb, planckf, plancko,
	   tref, emis,
	   rawvaluemedian, rawvaluerange);

  

  
  thermalMetadata tdata(planckr1, planckr2,
			planckb, planckf, plancko,
			tref, emis,
			rawvaluemedian, rawvaluerange);
  thermalMetadataValues = tdata;
  
  // print exiftool stderr messages
  char *err = et->GetError();
  if (err) cerr << err;
  delete et;      // delete our ExifTool object
}
