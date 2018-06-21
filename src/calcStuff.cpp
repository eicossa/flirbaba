#include <iostream>
#include <math>
#include "../inc/readTags.hpp"

using namespace std;

double calcRAWmax()
{
  double rawvaluemedian, rawvaluerange, rawmax;
  rawvaluemedian = getRAWvaluemedian();
  rawvaluerange  = getRAWvaluerange();

  rawmax = rawvaluemedian + (rawvaluerange/2);
  return rawmax;
}

double calcRAWmin()
{
  double rawmax, rawvaluerange, rawmin;
  rawmax        = calcRAWmax();
  rawvaluerange = getRAWvaluerange();

  rawmin = rawmax - rawvaluerange;
  return rawmin;
}

double calcRAWrefl()
{
  double planckr1, planckr2;
  double planckb, planckf;
  double tref;
  double rawrefl;

  double t11, t12, t13, t14;

  planckr1 = getPlanckR1();
  planckr2 = getPlanckR2();
  planckb  = getPlanckB();
  planckf  = getPlanckF();
  tref     = getTref();
  
  t11 = ((planckb) / (tref + 273.15));
  t12 = t11 - planckf;
  t13 = planckr2 * exp(t11);
  t14 = planckr1/t12;
  
  rawrefl = t13 - plancko;
  return rawrefl;

}

double calcRAWmaxobj()
{
  double rawmaxobj, rawmax, emis, rawrefl;
  rawmax    = calcRAWmax();
  emis      = getEmis();
  rawrefl   = calcRAWrefl();
  rawmaxobj = (rawmax - (1-emis)*rawrefl)/emis;
  return rawmaxobj;
}

double calcRAWminobj()
{
  double rawminobj, rawmin, emis, rawrefl;
  rawmin    = calcRAWmin();
  emis      = getEmis();
  rawrefl   = calcRAWrefl();
  rawminobj = (rawmin - (1-emis)*rawrefl)/emis;
  return rawminobj;
}

double calcTmin()
{
  double planckr1, planckr2;
  double planckb, planckf, plancko;
  double rawminobj;
  double tmin;
  double t21, t22, t23;

  planckr1  = getPlanckR1();
  planckr2  = getPlanckR2();
  planckb   = getPlanckB();
  planckf   = getPlanckF();
  plancko   = getPlanckO();
  rawminobj = calcRAWminobj();
  
  t21 = (planckr2 * (rawminobj + plancko) + planckf);
  //cout << " Tmin t21 : " << t21 << endl;
  t22 = (planckr1/t21) - 273.15;
  //cout << " Tmin t22 : " << t22 << endl;
  t23 = log(-t22);
  //cout << " Tmin t23 : " << t23 << endl;
  
  tmin = planckb / t23;
  //cout << " Tmin     : " << tmin << endl;
  return tmin;
}

double calcTmax()
{
  double planckr1, planckr2;
  double planckb, planckf, plancko;
  double rawmaxobj;
  double tmax;
  double t31, t32, t33;

  planckr1  = getPlanckR1();
  planckr2  = getPlanckR2();
  planckb   = getPlanckB();
  planckf   = getPlanckF();
  plancko   = getPlanckO();
  rawmaxobj = calcRAWmaxobj();

  t31 = (planckr2 * (rawmaxobj + plancko) + planckf);
  //cout << " Tmax t31 : " << t31 << endl;
  t32 = (planckr1/t31) - 273.15;
  //cout << " Tmax t32 : " << t32 << endl;
  t33 = log(-t32);
  //cout << " Tmax t33 : " << t33 << endl;

  tmax = planckb / t33;
  //cout << " Tmax     : " << tmax << endl;
  return tmax;
}


void calcSmax()
{
  double planckr1, planckr2;
  double planckb, planckf, plancko;
  double rawmax;
  double t41, t42, t43;

  planckr1  = getPlanckR1();
  planckr2  = getPlanckR2();
  planckb   = getPlanckB();
  planckf   = getPlanckF();
  plancko   = getPlanckO();
  rawmax    = calcRAWmax();

  
  double t41 = planckr2 * (rawmax + plancko);
  //cout << " Smax t41 : " << t41 << endl;
  double t42 = ((planckr1/t41) + planckf);
  //cout << " Smax t42 : " << t42 << endl;
  double t43 = log(t42);
  //cout << " Smax t43 : " << t43 << endl;
  
  Smax = planckb / t43;
  //cout << " Smax    : " << Smax << endl;
  return Smax;
}

double calcSmin()
{
  double planckr1, planckr2;
  double planckb, planckf, plancko;
  double rawmin;
  double t51, t52, t53;

  planckr1  = getPlanckR1();
  planckr2  = getPlanckR2();
  planckb   = getPlanckB();
  planckf   = getPlanckF();
  plancko   = getPlanckO();
  rawmin    = calcRAWmin();

  t51 = planckr2 * (rawmin + plancko);
  //cout << " Smin t51 : " << t51 << endl;
  t52 = ((planckr1/t51) + planckf);
  //cout << " Smin t52 : " << t52 << endl;
  t53 = log(t52);
  //cout << " Smin t53 : " << t53 << endl;
  
  Smin = planckb / t53;
  //cout << " Smin    : " << Smin << endl;
  return Smin;
}

double calcSdelta()
{
  double Smax, Smin, Sdelta;
  Smax   = calcSmax();
  Smin   = calcSmin();
  Sdelta = Smax - Smin;
  //cout << " Sdelta  : " << Sdelta << endl;
  return Sdelta;
}



double calculateTemperature(double thermalintensityvalue)
{
  double t61 = (65535 * thermalintensityvalue + plancko);
  double t62 = planckr2 * t61;
  double t63 = planckr1/(t62 + planckf);
  double t64 = log(t63);
  double t65 = t64 - Smin;
  double t66 = planckb/t65;
  double t67 = t66/Sdelta;

  cout<<" ... for thermal intensity of " << thermalintensityvalue << endl;
  cout<<" ... Exif Consts  " << planckr1 << " "
                             << planckr2 << " "
                             << planckb  << " "
                             << planckf  << " "
                             << plancko  <<endl;
  cout<<" ... Intermed temps  " << t61 << " | "
                                << t62 << " | "
                                << t63 << " | "
                                << t64 << " | "
                                << t65 << " | "
                                << t66 << " | "
                                << endl;
  cout<<" ... " << endl;
  return t67;
}
