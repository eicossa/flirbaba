#include "../inc/flirImgMetadata.hpp"

flirImgMetadata::flirImgMetadata()
{
  imgpath = "";
  planckr1 = 0.0;
  planckr2 = 0.0;
  planckb = 0.0;
  planckf = 0.0;
  plancko = 0.0;
  
  tref = 0.0;
  emis = 0.0;
  
  rawvaluerange = 0.0;
  rawvaluemedian = 0.0;
  
  // read basic metadata
  imagewidth = -1;
  imageheight = -1;
  rawthermalimagewidth = -1;
  rawthermalimageheight = -1;
  // calculated values
  rawmin = 0.0;
  rawmax = 0.0;
  rawrefl = 0.0;
  rawminobj = 0.0;
  rawmaxobj = 0.0;
  
  tmin = 0.0;
  tmax = 0.0;
  
  smin = 0.0;
  smax = 0.0;
  sdelta = 0.0;

}

flirImgMetadata::flirImgMetadata(std::string imgpath)
{
    this->imgpath = imgpath;
    cout << "Inside constructor : " << imgpath <<endl;
    
    readAllMetadata();
    calcAllMetadata();

    checkReadMetadata();
    checkCalcedMetadata();
 
}




void flirImgMetadata::readAllMetadata()
{
  readThermalMetadata();
  readBasicMetadata();
}


void flirImgMetadata::calcAllMetadata()
{
  calcRaws();
  calcTs();
  calcSes();
}



void flirImgMetadata::calcRaws()
{
  calcRAWmax();
  calcRAWmin();
  calcRAWrefl();
  calcRAWmaxobj();
  calcRAWminobj();
}

void flirImgMetadata::calcTs()
{
  calcTmin();
  calcTmax();
}

void flirImgMetadata::calcSes()
{
  calcSmin();
  calcSmax();
  calcSdelta();
}

void flirImgMetadata::readBasicMetadata()
{
  imagewidth  = readExiftoolTagInfo("ImageWidth");
  imageheight = readExiftoolTagInfo("ImageHeight");
  rawthermalimagewidth=readExiftoolTagInfo("RawThermalImageWidth");
  rawthermalimageheight=readExiftoolTagInfo("RawThermalImageHeight");
}

void flirImgMetadata::readThermalMetadata()
{
  // plancks
  planckr1 = readExiftoolTagInfo("PlanckR1");
  planckr2 = readExiftoolTagInfo("PlanckR2");
  planckb  = readExiftoolTagInfo("PlanckB");
  planckf  = readExiftoolTagInfo("PlanckF");
  plancko  = readExiftoolTagInfo("PlanckO");

  // tref and emis
  tref     = readExiftoolTagInfo("Tref");
  emis     = readExiftoolTagInfo("Emis");

  // raw values
  rawvaluerange =  readExiftoolTagInfo("RAWvaluerange");
  rawvaluemedian = readExiftoolTagInfo("RAWvaluemedian");

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
  //checkRAWvaluemedian();
  //checkRAWvaluerange();

  rawmax = rawvaluemedian + (rawvaluerange/2);
}

void flirImgMetadata::calcRAWmin()
{
  //checkRAWvaluerange();
  //checkRAWmax();

  rawmin = rawmax - rawvaluerange;
}


// an optional thaaang if tref & RAWrefl are defined
// in the metadata
void flirImgMetadata::calcRAWrefl()
{
  //checkPlancks();
  //checkTref();
  //checkRAWrefl();

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
  //checkRAWmax();
  //checkEmis();
  //checkRAWrefl();
  
  rawmaxobj = (rawmax - (1-emis)*rawrefl)/emis;
}

void flirImgMetadata::calcRAWminobj()
{
  //checkRAWmin();
  //checkEmis();
  //checkRAWrefl();
  
  rawminobj = (rawmin - (1-emis)*rawrefl)/emis;
}

void flirImgMetadata::calcTmin()
{
  //checkPlancks();
  //checkRAWminobj();
  double t21, t22, t23, t24;
  
  t21 = (rawminobj + plancko);
  t22 = planckr2 * t21;
  t23 = (planckr1/t22) + planckf;
  t24 = planckb / log(t23);
  tmin = t24 - 273.15;
}

void flirImgMetadata::calcTmax()
{
  //checkPlancks();
  //checkRAWmaxobj();
  double t31, t32, t33, t34;

  t31 = (rawmaxobj + plancko);
  t32 = planckr2 * t31;
  t33 = (planckr1/t32) + planckf;
  t34 = planckb / log(t33);
  tmax = t34 - 273.15;
}


void flirImgMetadata::calcSmax()
{
  //checkPlancks();
  //checkRAWmax();
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
  //checkPlancks();
  //checkRAWmin();
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
  //checkSmax();
  //checkSmin();
  
  sdelta = smax - smin;
}

double flirImgMetadata::calcTempForOnePixel(double thermalintensityvalue)
{
  double t61, t62, t63, t64, t65, t66, t67;
  // just linearly mapped the thermal intensity values to a value between
  // rawminobj and rawmaxobj using
  // https://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another

  //cout << "ThermalIntensityValue " << thermalintensityvalue;
  t61 = rawminobj + ((rawmaxobj-rawminobj)/(65535))*(thermalintensityvalue);
  // cout << "t61 : " << t61 << endl;
  //t61 = 13900;
  t62 = t61 + plancko;
  t63 = planckr2 * t62;
  t64 = (planckr1/t63) + planckf;
  //t65 = planckb/log(t64) - smin;
  t65 = planckb/log(t64);
  //t66 = t65/sdelta;
  t66 = t65 - 273.15;

  return t66;
}


double flirImgMetadata::readExiftoolTagInfo(std::string tagname)
{
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
  cout << "RAWmax         : "     << rawmax         << endl;
  cout << "RAWmin         : "     << rawmin         << endl;
  cout << "RAWrefl        : "     << rawrefl        << endl;
  cout << "RAWmaxobj      : "     << rawmaxobj      << endl;
  cout << "RAWminobj      : "     << rawminobj      << endl;

  cout << "\n\n Tmin, Tmax ..." << endl;
  cout << "Tmin    : "          << tmin   << endl;
  cout << "Tmax    : "          << tmax   << endl;

  cout << "\n\n Smax, Smin, Sdelta calculated ..." << endl;
  cout << "Smax    : "          << smax   << endl;
  cout << "Smin    : "          << smin   << endl;
  cout << "Sdelta  : "          << sdelta << endl;

}

void flirImgMetadata::printReadMetadata()
{
  cout << "PlanckR1       : " << planckr1       << endl;
  cout << "PlanckR2       : " << planckr2       << endl;
  cout << "PlanckB        : " << planckb        << endl;
  cout << "PlanckF        : " << planckf        << endl;
  cout << "PlanckO        : " << plancko        << endl;
  cout << "Tref           : " << tref           << endl;
  cout << "Emis           : " << emis           << endl;
  cout << "RawValueMedian : " << rawvaluemedian << endl;
  cout << "RawValueRange  : " << rawvaluerange  << endl;

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
  cout << " | PlanckR1       : " << setw(10) << planckr1
       << " | RAWmax         : " << setw(10) << rawmax
       << " | Tmin    : "        << setw(10) << tmin
       << " | Smax    : "        << setw(10) << smax   << endl;
  cout << " | PlanckR2       : " << setw(10) << planckr2
       << " | RAWmin         : " << setw(10) << rawmin    
       << " | Tmax    : "        << setw(10) << tmax
       << " | Smin    : "        << setw(10) << smin   << endl;
  cout << " | PlanckB        : " << setw(10) << planckb
       << " | RAWrefl        : " << setw(10) << rawrefl   
       << setw(23) << ""
       << " | Sdelta   : " << setw(10) << sdelta << endl;
  cout << " | PlanckF        : " << setw(10) << planckf
       << " | RAWmaxobj      : " << setw(10) << rawmaxobj << endl;
  cout << " | PlanckO        : " << setw(10) << plancko
       << " | RAWminobj      : " << setw(10) << rawminobj << endl;
  cout << " | Tref           : " << setw(10) << tref           << endl;
  cout << " | Emis           : " << setw(10) << emis           << endl;
  cout << " | RawValueMedian : " << setw(10) << rawvaluemedian << endl;
  cout << " | RawValueRange  : " << setw(10) << rawvaluerange  << endl;

}
