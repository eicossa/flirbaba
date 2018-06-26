#include <iostream>
#include "../inc/printStuff.hpp"
#include "../inc/readTags.hpp"
#include "../inc/calcStuff.hpp"
#include "../inc/flirImg.hpp"
using namespace std;

void flirImg::printImageSummary()
{
  //cout << "\n\n\nExiftags read .... "            << endl;
  cout << " | PlanckR1       : " << setw(10) << getPlanckR1()
       << " | RAWmax         : " << setw(10) << calcRAWmax()
       << " | Tmin    : "        << setw(10) << calcTmin()
       << " | Smax    : "        << setw(10) << calcSmax()   << endl;
  cout << " | PlanckR2       : " << setw(10) << getPlanckR2()
       << " | RAWmin         : " << setw(10) << calcRAWmin()    
       << " | Tmax    : "        << setw(10) << calcTmax()
       << " | Smin    : "        << setw(10) << calcSmin()   << endl;
  cout << " | PlanckB        : " << setw(10) << getPlanckB()
       << " | RAWrefl        : " << setw(10) << calcRAWrefl()   
       << setw(23) << ""
       << " | Sdelta   : " << setw(10) << calcSdelta() << endl;
  cout << " | PlanckF        : " << setw(10) << getPlanckF()
       << " | RAWmaxobj      : " << setw(10) << calcRAWmaxobj() << endl;
  cout << " | PlanckO        : " << setw(10) << getPlanckO()
       << " | RAWminobj      : " << setw(10) << calcRAWminobj() << endl;
  cout << " | Tref           : " << setw(10) << getTref()           << endl;
  cout << " | Emis           : " << setw(10) << getEmis()           << endl;
  cout << " | RawValueMedian : " << setw(10) << getRAWvaluemedian() << endl;
  cout << " | RawValueRange  : " << setw(10) << getRAWvaluerange()  << endl;
}


void flirImg::printExifThermalTags()
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

void flirImg::calcRaws()
{
  cout << "\n\n\nRaws calculated" << endl;
  cout << "RAWmax         : "     << calcRAWmax()         << endl;
  cout << "RAWmin         : "     << calcRAWmin()         << endl;
  cout << "RAWrefl        : "     << calcRAWrefl()        << endl;
  cout << "RAWmaxobj      : "     << calcRAWmaxobj()      << endl;
  cout << "RAWminobj      : "     << calcRAWminobj()      << endl;
}


void flirImg::printMaxMinTemps()
{
  cout << "\n\n Tmin, Tmax ..." << endl;
  cout << "Tmin    : "             << calcTmin()   << endl;
  cout << "Tmax    : "             << calcTmax()   << endl;

}

void flirImg::printSes()
{
  cout << "\n\n Smax, Smin, Sdelta calculated ..." << endl;
  cout << "Smax    : "             << calcSmax()   << endl;
  cout << "Smin    : "             << calcSmin()   << endl;
  cout << "Sdelta  : "             << calcSdelta() << endl;
}


