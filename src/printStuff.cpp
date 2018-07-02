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
       << " | RAWmax         : " << setw(10) << getRAWmax()
       << " | Tmin    : "        << setw(10) << getTmin()
       << " | Smax    : "        << setw(10) << getSmax()   << endl;
  cout << " | PlanckR2       : " << setw(10) << getPlanckR2()
       << " | RAWmin         : " << setw(10) << getRAWmin()    
       << " | Tmax    : "        << setw(10) << getTmax()
       << " | Smin    : "        << setw(10) << getSmin()   << endl;
  cout << " | PlanckB        : " << setw(10) << getPlanckB()
       << " | RAWrefl        : " << setw(10) << getRAWrefl()   
       << setw(23) << ""
       << " | Sdelta   : " << setw(10) << getSdelta() << endl;
  cout << " | PlanckF        : " << setw(10) << getPlanckF()
       << " | RAWmaxobj      : " << setw(10) << getRAWmaxobj() << endl;
  cout << " | PlanckO        : " << setw(10) << getPlanckO()
       << " | RAWminobj      : " << setw(10) << getRAWminobj() << endl;
  cout << " | Tref           : " << setw(10) << getTref()           << endl;
  cout << " | Emis           : " << setw(10) << getEmis()           << endl;
  cout << " | RawValueMedian : " << setw(10) << getRAWvaluemedian() << endl;
  cout << " | RawValueRange  : " << setw(10) << getRAWvaluerange()  << endl;
}


void flirImg::printMetadata()
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
  cout << "RAWmax         : "     << getRAWmax()         << endl;
  cout << "RAWmin         : "     << getRAWmin()         << endl;
  cout << "RAWrefl        : "     << getRAWrefl()        << endl;
  cout << "RAWmaxobj      : "     << getRAWmaxobj()      << endl;
  cout << "RAWminobj      : "     << getRAWminobj()      << endl;
}


void flirImg::printMaxMinTemps()
{
  cout << "\n\n Tmin, Tmax ..." << endl;
  cout << "Tmin    : "          << getTmin()   << endl;
  cout << "Tmax    : "          << getTmax()   << endl;

}

void flirImg::printSes()
{
  cout << "\n\n Smax, Smin, Sdelta calculated ..." << endl;
  cout << "Smax    : "          << getSmax()   << endl;
  cout << "Smin    : "          << getSmin()   << endl;
  cout << "Sdelta  : "          << getSdelta() << endl;
}


