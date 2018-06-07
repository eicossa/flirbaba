#include <iostream>
#include "../inc/printStuff.h"
using namespace std;

void printThermalTags(double planckr1, double planckr2,
              	      double planckb, double planckf, double plancko,
		      double tref, double emis,
		      double rawvaluemedian, double rawvaluerange)
{
  cout << "\n\n\nExiftags read .... "           << endl;
  cout << "PlanckR1       : " << planckr1       << endl;
  cout << "PlanckR2       : " << planckr2       << endl;
  cout << "PlanckB        : " << planckb        << endl;
  cout << "PlanckF        : " << planckf        << endl;
  cout << "PlanckO        : " << plancko        << endl;
  cout << "Tref           : " << tref           << endl;
  cout << "Emis           : " << emis           << endl;
  cout << "RawValueMedian : " << rawvaluemedian << endl;
  cout << "RawValueRange  : " << rawvaluerange  << endl;
}

void printRawSensorCalcs()
{
  // separate out the raw thermal data from the FLIR image
  extractRawThermaldata(rgbimgpath, thermdataimgpath);

  printThermalTags();
  printMaxMinRAW();
  printMaxMinTempsInImage();
}


void printImageSummary()
{
  readExifTags();

}

void printMaxMinTempsInImage()
{


}


void thermalMetadata::printRaws()
{
  cout << "\n\n\nRaws calculated" << endl;
  cout << "RAWmax         : "     << rawmax << endl;
  cout << "RAWmin         : "     << rawmin << endl;
  cout << "RAWrefl        : "     << rawrefl << endl;
  cout << "RAWmaxobj      : "     << rawmaxobj << endl;
  cout << "RAWminobj      : "     << rawminobj << endl;
  //cout << "Tref           : "     << tref << endl;
  //cout << "Emis           : "     << emis << endl;
  cout << "RawValueMedian : "     << rawvaluemedian << endl;
  cout << "RawValueRange  : "     << rawvaluerange << endl;
  

  cout << "RAWmax    : " << rawmax  << endl;
  cout << "RAWmin    : " << rawmax  << endl;
  cout << "RAWrefl   : " << rawrefl << endl;
  cout << "RAWmaxobj : " << rawrefl << endl;
  cout << "RAWminobj : " << rawrefl << endl;

}


void thermalMetadata::printMaxMinTemps()
{
  cout << "\n\n\nDiffs calculated" << endl;
  cout << "Tmin    : "             << tmin  << endl;
  cout << "Tmax    : "             << tmax  << endl;
  cout << "Smax    : "             << Smax  << endl;
  cout << "Smin    : "             << Smin  << endl;
  cout << "Sdelta  : "             << Sdelta << endl;

}



void thermalMetadata::printThermalTags()
{

  cout << "\n\n\nMetadata delivered " << endl;
  cout << "PlanckR1 : "               << planckr1 << endl;
  cout << "PlanckR2 : "               << planckr2 << endl;
  cout << "PlanckB : "                << planckb << endl;
  cout << "PlanckF : "                << planckf << endl;
  cout << "PlanckO : "                << plancko << endl;
  cout << "Tref : "                   << tref << endl;
  cout << "Emis : "                   << emis << endl;
  cout << "RawValueMedian : "         << rawvaluemedian << endl;
  cout << "RawValueRange : "          << rawvaluerange << endl;

}


