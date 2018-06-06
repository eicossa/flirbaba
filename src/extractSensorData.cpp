using namespace std;

void extractRawThermaldata(const char* imgpath, std::string &rawthermdataimagename)
{
  rawthermdataimagename   = imgpath + std::string(".rawthermout.png");
  std::string rawthermaldatacmdstring = std::string("exiftool ")
                                        + imgpath
                                        + std::string(" -rawthermalimage -b")
                                        + std::string(" | convert - grayscale:- ")
                                        + std::string(" | convert -depth 16 -endian msb grayscale:- -auto-level ")
                                        + rawthermdataimagename;

  std::string output;
  output = exec(rawthermaldatacmdstring);
  cout << output << endl;
  //rawthermdataimgpath = rawthermdataimagename.c_str();
}
