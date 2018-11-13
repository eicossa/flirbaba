#include "../inc/flirImgMetadata.hpp"

flirImgMetadata::flirImgMetadata(std::string imgpath)
{
  readAllMetadata();
  calcAllMetadata();

  checkReadMetadata();
  checkCalcedMetadata();
}

void readAllMetadata()
{
  readThermalMetadata();
  readBasicMetadata();
}

void calcAllMetadata()
{
  calcRaws();
  calcTs();
  calcSes();
}



void calcRaws()
{
  calcRAWmax();
  calcRAWmin();
  calcRAWrefl();
  calcRAWmaxobj();
  calcRAWminobj();
}

void calcTs()
{
  calcTmin();
  calcTmax();
}

void calcSes()
{
  calcSmin();
  calcSmax();
  calcSdelta();
}



void readThermalMetadata()
{
  // plancks
  planckr1 = readPlanckR1();
  planckr2 = readPlanckR2();
  planckb  = readPlanckB();
  planckf  = readPlanckF();
  plancko  = readPlanckO();
  
  // tref & emis
  tref     = readTref();
  emis     = readEmis();
  
  // raw value  
  rawvaluerange  = readRAWvaluerange();
  rawvaluemedian = readRAWvaluemedian();
}



void readBasicMetadata()
{
  imagewidth  = getExiftoolTagInfo("ImageWidth");
  imageheight = getExiftoolTagInfo("ImageHeight");
  rawthermalimagewidth=getExiftoolTagInfo("RawThermalImageWidth");
  rawthermalimageheight=getExiftoolTagInfo("RawThermalImageHeight");
}

void readThermalMetadata()
{
  planckr1 = getExiftoolTagInfo("PlanckR1");
  planckr2 = getExiftoolTagInfo("PlanckR2");
  planckb  = getExiftoolTagInfo("PlanckB");
  planckf  = getExiftoolTagInfo("PlanckF");
  plancko  = getExiftoolTagInfo("PlanckO");
  tref     = getExiftoolTagInfo("Tref");
  emis     = getExiftoolTagInfo("Emis");
  rawvaluerange =  getExiftoolTagInfo("RAWvaluerange");
  rawvaluemedian = getExiftoolTagInfo("RAWvaluemedian");

}


void flirImgMetadata::checkReadMetadata()
{
    assert(planckr1 != 0);
    assert(planckr2 != 0);
    assert(planckb  != 0);
    assert(planckf  != 0);
    assert(plancko  != 0);
    assert(rawvaluemedian != 0);
    assert(rawvaluerange  != 0);
    assert(tref           != 0);
    assert(emis           != 0);
    assert(rawrefl        != 0);
}

void flirImgMetadata::checkCalcedMetadata()
{
  assert(rawmax   != 0);
  assert(rawmin   != 0);
  assert(rawmaxobj != 0);
  assert(rawminobj != 0);
  assert(tmin      != 0);
  assert(tmax      != 0);
  assert(smax != 0);
  assert(smin != 0);
  assert(sdelta != 0);

}

void flirImgMetadata::calcRAWmax()
{
  checkRAWvaluemedian();
  checkRAWvaluerange();

  rawmax = rawvaluemedian + (rawvaluerange/2);
}

void flirImgMetadata::calcRAWmin()
{
  checkRAWvaluerange();
  checkRAWmax();

  rawmin = rawmax - rawvaluerange;
}


// an optional thaaang if tref & RAWrefl are defined
// in the metadata
void flirImgMetadata::calcRAWrefl()
{
  checkPlancks();
  checkTref();
  checkRAWrefl();

  double t11, t12, t13, t14, t15;

  tref = 25;
  t11 = tref + 273.15; 
 //cout << "\n t11 " << t11;
  t12 = planckb / t11;
  //cout << "\n t12 " << t12;
  t13 = exp(t12) - planckf;
  //cout << "\n t13 " << t13;
  t14 = planckr2 * t13;
  //cout << "\n t14 " << t14;
  t15 = planckr1 / t14;
  //cout << "\n t15 " << t15;
  
  rawrefl = t15 - plancko;
  //cout << "\n t16 " << rawrefl << endl;
}

void flirImgMetadata::calcRAWmaxobj()
{
  checkRAWmax();
  checkEmis();
  checkRAWrefl();
  
  rawmaxobj = (rawmax - (1-emis)*rawrefl)/emis;
}

void flirImgMetadata::calcRAWminobj()
{
  checkRAWmin();
  checkEmis();
  checkRAWrefl();
  
  rawminobj = (rawmin - (1-emis)*rawrefl)/emis;
}

void flirImgMetadata::calcTmin()
{
  checkPlancks();
  checkRAWminobj();
  double t21, t22, t23, t24;
  
  t21 = (rawminobj + plancko);
  t22 = planckr2 * t21;
  t23 = (planckr1/t22) + planckf;
  t24 = planckb / log(t23);
  tmin = t24 - 273.15;
}

void flirImgMetadata::calcTmax()
{
  checkPlancks();
  checkRAWmaxobj();
  double t31, t32, t33, t34;

  t31 = (rawmaxobj + plancko);
  t32 = planckr2 * t31;
  t33 = (planckr1/t32) + planckf;
  t34 = planckb / log(t33);
  tmax = t34 - 273.15;
}


void flirImgMetadata::calcSmax()
{
  checkPlancks();
  checkRAWmax();
  double t41, t42, t43;
  
  t41 = planckr2 * (rawmax + plancko);
  //cout << " Smax t41 : " << t41 << endl;
  t42 = ((planckr1/t41) + planckf);
  //cout << " Smax t42 : " << t42 << endl;
  t43 = log(t42);
  //cout << " Smax t43 : " << t43 << endl;
  
  smax = planckb / t43;
}

void flirImgMetadata::calcSmin()
{
  checkPlancks();
  checkRAWmin();
  //double planckr1, planckr2;
  //double planckb, planckf, plancko;
  //double rawmin;
  //double Smin;
  double t51, t52, t53;

  t51 = planckr2 * (rawmin + plancko);
  //cout << " Smin t51 : " << t51 << endl;
  t52 = ((planckr1/t51) + planckf);
  //cout << " Smin t52 : " << t52 << endl;
  t53 = log(t52);
  //cout << " Smin t53 : " << t53 << endl;
  
  smin = planckb / t53;
  //cout << " Smin    : " << Smin << endl;
}

void flirImgMetadata::calcSdelta()
{
  checkSmax();
  checkSmin();
  
  sdelta = smax - smin;
}















double flirImgMetadata::readExiftoolTagInfo(std::string tagname)
{
  std::string imgpath;
  std::string readtaglist;

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











void flirImgMetadata::printCalcedMetadata()
{
  cout << "\n\n\nRaws calculated" << endl;
  cout << "RAWmax         : "     << getRAWmax()         << endl;
  cout << "RAWmin         : "     << getRAWmin()         << endl;
  cout << "RAWrefl        : "     << getRAWrefl()        << endl;
  cout << "RAWmaxobj      : "     << getRAWmaxobj()      << endl;
  cout << "RAWminobj      : "     << getRAWminobj()      << endl;

  cout << "\n\n Tmin, Tmax ..." << endl;
  cout << "Tmin    : "          << getTmin()   << endl;
  cout << "Tmax    : "          << getTmax()   << endl;

  cout << "\n\n Smax, Smin, Sdelta calculated ..." << endl;
  cout << "Smax    : "          << getSmax()   << endl;
  cout << "Smin    : "          << getSmin()   << endl;
  cout << "Sdelta  : "          << getSdelta() << endl;

}

void flirImgMetadata::printReadMetadata()
{
  cout << "PlanckR1       : " << getPlanckR1()       << endl;
  cout << "PlanckR2       : " << getPlanckR2()       << endl;
  cout << "PlanckB        : " << getPlanckB()        << endl;
  cout << "PlanckF        : " << getPlanckF()        << endl;
  cout << "PlanckO        : " << getPlanckO()        << endl;
  cout << "Tref           : " << getTref()           << endl;
  cout << "Emis           : " << getEmis()           << endl;
  cout << "RawValueMedian : " << getRAWvaluemedian() << endl;
  cout << "RawValueRange  : " << getRAWvaluerange()  << endl;

  cout << "--------------------------------" << endl;
  
  cout << "ImageWidth  : " << imagewidth << endl;
  cout << "ImageHeight : " << imageheight << endl;

  cout << "RawThermalImageWidth  : " << rawthermalimagewidth << endl;
  cout << "RawThermalImageHeight : " << rawthermalimageheight << endl;


  cout << "--------------------------------" << endl;
}


void flirImgMetadata::printImageSummary()
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
