#include "../inc/flirImg.hpp"
#include <cassert>

// check metadata
void flirImg::checkRAWvaluemedian()
{
  assert(rawvaluemedian != 0);
}

void flirImg::checkRAWvaluerange()
{
  assert(rawvaluerange  != 0);
}

// void flirImg::checkRAWmax()
// {
//   assert(rawmax         != 0);
// }

void flirImg::checkTref()
{
  assert(tref           != 0);
}

void flirImg::checkEmis()
{
  assert(emis           != 0);
}

void flirImg::checkRAWrefl()
{
  assert(rawrefl        != 0);
}

void flirImg::checkPlancks()
{
  assert(planckr1 != 0);
  assert(planckr2 != 0);
  assert(planckb  != 0);
  assert(planckf  != 0);
  assert(plancko  != 0);
}


// check calcs

void flirImg::checkRAWmax()
{
  assert(rawmax   != 0);
}

void flirImg::checkRAWmin()
{
  assert(rawmin   != 0);
}

void flirImg::checkRAWmaxobj()
{
  assert(rawmaxobj != 0);
}

void flirImg::checkRAWminobj()
{
  assert(rawminobj != 0);
}

void flirImg::checkTmin()
{
  assert(tmin      != 0);
}

void flirImg::checkTmax()
{
  assert(tmax      != 0);
}

void flirImg::checkSmax()
{
  assert(smax != 0);
}

void flirImg::checkSmin()
{
  assert(smin != 0);
}

void flirImg::checkSdelta()
{
  assert(sdelta != 0);
}


// check everythin
void flirImg::checkEverything()
{

}
