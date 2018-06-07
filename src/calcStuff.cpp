void thermalMetadata::calculateRaws()
{
  rawmax  = rawvaluemedian + (rawvaluerange/2);
  
  rawmin = rawmax - rawvaluerange;
  cout << "RAWmax    : " << rawmax  << endl;
  cout << "RAWmin    : " << rawmax  << endl;
  cout << "RAWrefl   : " << rawrefl << endl;
  cout << "RAWmaxobj : " << rawrefl << endl;
  cout << "RAWminobj : " << rawrefl << endl;

  double t11 = ((planckb) / (tref + 273.15)) - planckf;
  double t12 = planckr2 * exp(t11);
  double t13 = planckr1/t12;
  
  rawrefl = t13 - plancko;
  

  rawmaxobj = (rawmax - (1-emis)*rawrefl)/emis;
  
  rawminobj = (rawmin - (1-emis)*rawrefl)/emis;
  
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
