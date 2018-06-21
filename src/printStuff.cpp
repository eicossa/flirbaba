#include <iostream>
#include "../inc/printStuff.h"
using namespace std;

void printThermalTags()
{
  cout << "\n\n\nExiftags read .... "                << endl;
  cout << "PlanckR1       : " << getPlanckR1()       << endl;
  cout << "PlanckR2       : " << getPlanckR2()       << endl;
  cout << "PlanckB        : " << getPlanckB()        << endl;
  cout << "PlanckF        : " << getPlanckF()        << endl;
  cout << "PlanckO        : " << getPlanckO()        << endl;
  cout << "Tref           : " << getTref()           << endl;
  cout << "Emis           : " << getEmis()           << endl;
  cout << "RawValueMedian : " << getRawValueMedian() << endl;
  cout << "RawValueRange  : " << getRawValueRange()  << endl;
}

static void printRawSensorCalcs()
{
  // separate out the raw thermal data from the FLIR image
  extractRawThermaldata(rgbimgpath, thermdataimgpath);

  printThermalTags();
  printMaxMinRAW();
  printMaxMinTempsInImage();
}


static void printImageSummary()
{
  readExifTags();

}

static void printMaxMinTempsInImage()
{


}


static void printRaws()
{
  cout << "\n\n\nRaws calculated" << endl;
  cout << "RAWmax         : "     << getRAWmax()         << endl;
  cout << "RAWmin         : "     << getRAWmin()         << endl;
  cout << "RAWrefl        : "     << getRAWrefl()        << endl;
  cout << "RAWmaxobj      : "     << getRAWmaxobj()      << endl;
  cout << "RAWminobj      : "     << getRAWminobj()      << endl;
  cout << "Tref           : "     << getTref()           << endl;
  cout << "Emis           : "     << getEmis()           << endl;
  cout << "RawValueMedian : "     << getRAWvaluemedian() << endl;
  cout << "RawValueRange  : "     << getRAWvaluerange()  << endl;
}


static void printMaxMinTemps()
{
  cout << "\n\n\nDiffs calculated" << endl;
  cout << "Tmin    : "             << getTmin()   << endl;
  cout << "Tmax    : "             << getTmax()   << endl;
  cout << "Smax    : "             << getSmax()   << endl;
  cout << "Smin    : "             << getSmin()   << endl;
  cout << "Sdelta  : "             << getSdelta() << endl;
}



