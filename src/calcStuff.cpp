#include <iostream>
#include <cmath>
#include "../inc/readTags.hpp"
#include "../inc/flirImgMetadata.hpp"

using namespace std;

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


void flirImgMetadata::calcEverything()
{
  calcRAWmax();
  calcRAWmin();
  calcRAWrefl();
  calcRAWmaxobj();
  calcRAWminobj();
  
  calcTmin();
  calcTmax();
  calcSmin();
  calcSmax();
  calcSdelta();


}


