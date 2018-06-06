using namespace std;

class exifTagdata{
  double planckr1;
  double planckr2;
  double planckb;
  double planckf;
  double plancko;
  
  double tref;
  double emis;
  
  double rawvaluemedian;
  double rawvaluerange;

  double rawmin;
  double rawmax;
  double rawrefl;
  double rawmaxobj;
  double rawminobj;

  double tmax;
  double tmin;

  double Smax;
  double Smin;
  double Sdelta;
  
  
public:
  thermalMetadata()
  {
    this->planckr1 = -1;
    this->planckr2 = -1;
    this->planckb  = -1;
    this->planckf  = -1;
    this->plancko  = -1;
    this->tref     = -1;
    this->emis     = -1;
    this->rawvaluemedian = -1;
    this->rawvaluerange  = -1;
  }
  
  thermalMetadata(double planckr1, double planckr2,
			  double planckb, double planckf, double plancko,
			  double tref, double emis,
		  double rawvaluemedian, double rawvaluerange)
  {
    this->planckr1 = planckr1;
    this->planckr2 = planckr2;
    this->planckb  = planckb;
    this->planckf  = planckf;
    this->plancko  = plancko;
    this->tref     = tref;
    this->emis     = emis;
    this->rawvaluemedian = rawvaluemedian;
    this->rawvaluerange  = rawvaluerange;
  }

  void setPreCalculations(double rawmin, double rawmax, double rawrefl,
			  double rawmaxobj, double rawminobj)
  {
    this->rawmin    = rawmin;
    this->rawmax    = rawmax;
    this->rawrefl   = rawrefl;
    this->rawmaxobj = rawmaxobj;
    this->rawminobj = rawminobj;

  }

  void calculateRaws();
  void calculateMaxMinTemperatures();
  double calculateTemperature(double thermalintensityvalue);
  
  void printConsts();
  void printRaws();
  void printMaxMinTemps();

};

void thermalMetadata::calculateRaws()
{
  rawmax  = rawvaluemedian + (rawvaluerange/2);
  cout << "RAWmax : " << rawmax << endl;
  rawmin  = rawmax - rawvaluerange;
  cout << "RAWmin : " << rawmax << endl;

  double t11 = ((planckb) / (tref + 273.15)) - planckf;
  double t12 = planckr2 * exp(t11);
  double t13 = planckr1/t12;
  
  rawrefl = t13 - plancko;
  cout << "RAWrefl : " << rawrefl << endl;

  rawmaxobj = (rawmax - (1-emis)*rawrefl)/emis;
  cout << "RAWmaxobj : " << rawrefl << endl;
  rawminobj = (rawmin - (1-emis)*rawrefl)/emis;
  cout << "RAWminobj : " << rawrefl << endl;
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
  

}


void thermalMetadata::calculateMaxMinTemperatures()
{
  double t21 = (planckr2 * (rawminobj + plancko) + planckf);
  cout << " Tmin t21 : " << t21 << endl;
  double t22 = (planckr1/t21) - 273.15;
  cout << " Tmin t22 : " << t22 << endl;
  double t23 = log(-t22);
  cout << " Tmin t23 : " << t23 << endl;
  
  tmin = planckb / t23;
  cout << " Tmin     : " << tmin << endl;

  double t31 = (planckr2 * (rawmaxobj + plancko) + planckf);
  cout << " Tmax t31 : " << t31 << endl;
  double t32 = (planckr1/t31) - 273.15;
  cout << " Tmax t32 : " << t32 << endl;
  double t33 = log(-t32);
  cout << " Tmax t33 : " << t33 << endl;

  tmax = planckb / t33;
  cout << " Tmax     : " << tmax << endl;

  double t41 = planckr2 * (rawmax + plancko);
  cout << " Smax t41 : " << t41 << endl;
  double t42 = ((planckr1/t41) + planckf);
  cout << " Smax t42 : " << t42 << endl;
  double t43 = log(t42);
  cout << " Smax t43 : " << t43 << endl;
  
  Smax = planckb / t43;
  cout << " Smax    : " << Smax << endl;

  double t51 = planckr2 * (rawmin + plancko);
  cout << " Smin t51 : " << t51 << endl;
  double t52 = ((planckr1/t51) + planckf);
  cout << " Smin t52 : " << t52 << endl;
  double t53 = log(t52);
  cout << " Smin t53 : " << t53 << endl;
  
  Smin = planckb / t53;
  cout << " Smin    : " << Smin << endl;

  Sdelta = Smax - Smin;
  cout << " Sdelta  : " << Sdelta << endl;
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


double thermalMetadata::calculateTemperature(double thermalintensityvalue)
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


void thermalMetadata::printConsts()
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
