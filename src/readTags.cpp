#include <inc/thermalMetadata.h>

void readTags(double &planckr1, double &planckr2,
	      double &planckb, double &planckf, double &plancko,
	      double &tref, double &emis,
	      double &rawvaluemedian, double &rawvaluerange)
{
  // create our ExifTool objetc
  ExifTool *et = new ExifTool();

  // read metadata from the image
  TagInfo *info = et->ImageInfo(imgpath, NULL, 5);
  if (info) {
    // print returned information
    for (TagInfo *i=info; i; i=i->next) {
      std::string tagname = i->name;
	  
      if(!ci_find_substr( tagname, std::string("PlanckR1"))){
	//cout << tagname << " : " << i-> value << endl;
	planckr1 = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("PlanckR2"))){
	//cout << tagname << " : " << i-> value << endl;
	planckr2 = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("PlanckB"))){
	//cout << tagname << " : " << i-> value << endl;
        planckb = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("PlanckF"))){
	//cout << tagname << " : " << i-> value << endl;
	planckf = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("PlanckO"))){
	//cout << tagname << " : " << i-> value << endl;
	plancko = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("ReflectedApparentTemperature"))){
	//cout << tagname << " : " << i-> value << endl;
	tref = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("Emissivity"))){
	//cout << tagname << " : " << i-> value << endl;
	emis = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("RawValueMedian"))){
	//cout << tagname << " : " << i-> value << endl;
	rawvaluemedian = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("RawValueRange"))){
	//cout << tagname << " : " << i-> value << endl;
	rawvaluerange = stod(i->value);
      } else {
	//cout << tagname << " : " << i->value << endl;
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

  //calculateTemperature(planckr1, planckr2,
  //       planckb, planckf, plancko,
  //		       tref, emis,
  //		       rawvaluemedian, rawvaluerange);
}
