#include <iostream>
#include "../inc/printStuff.hpp"
#include "../inc/readTags.hpp"
#include "../inc/calcStuff.hpp"
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
  cout << "RawValueMedian : " << getRAWvaluemedian() << endl;
  cout << "RawValueRange  : " << getRAWvaluerange()  << endl;
}

static void printRawSensorCalcs()
{
  // separate out the raw thermal data from the FLIR image
  //extractRawThermaldata(rgbimgpath, thermdataimgpath);

  //printThermalTags();
  //printMaxMinRAW();
  //printMaxMinTempsInImage();
}


// static void printImageSummary()
// {
//   readExifTags();

// }

// static void printMaxMinTempsInImage()
// {


// }


static void printRaws()
{
  cout << "\n\n\nRaws calculated" << endl;
  cout << "RAWmax         : "     << calcRAWmax()         << endl;
  cout << "RAWmin         : "     << calcRAWmin()         << endl;
  cout << "RAWrefl        : "     << calcRAWrefl()        << endl;
  cout << "RAWmaxobj      : "     << calcRAWmaxobj()      << endl;
  cout << "RAWminobj      : "     << calcRAWminobj()      << endl;
  cout << "Tref           : "     << getTref()           << endl;
  cout << "Emis           : "     << getEmis()           << endl;
  cout << "RawValueMedian : "     << getRAWvaluemedian() << endl;
  cout << "RawValueRange  : "     << getRAWvaluerange()  << endl;
}


static void printMaxMinTemps()
{
  cout << "\n\n\nDiffs calculated" << endl;
  cout << "Tmin    : "             << calcTmin()   << endl;
  cout << "Tmax    : "             << calcTmax()   << endl;
  cout << "Smax    : "             << calcSmax()   << endl;
  cout << "Smin    : "             << calcSmin()   << endl;
  cout << "Sdelta  : "             << calcSdelta() << endl;
}



