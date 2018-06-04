#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include "inc/ExifTool.h"
#include "inc/thermalMetadata.h"
#include "inc/suitcase.h"

using namespace std;
using namespace cv;

// templated version of my_equal so it could work with both char and wchar_t
template<typename charT>
struct my_equal {
    my_equal( const std::locale& loc ) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
int ci_find_substr( const T& str1,c onst T& str2, const std::locale& loc = std::locale() )
{
    typename T::const_iterator it = std::search( str1.begin(), str1.end(), 
        str2.begin(), str2.end(), my_equal<typename T::value_type>(loc) );
    if ( it != str1.end() ) return it - str1.begin();
    else return -1; // not found
}


// https://stackoverflow.com/questions/478898/
// how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
std::string exec(const std::string cmd) {
    std::array<char, 128> buffer;
    std::string result;

    const char* cmdstr = cmd.c_str();
    std::shared_ptr<FILE> pipe(popen(cmdstr, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}



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



void readExiftoolMetadata(const char* imgpath, thermalMetadata &thermalMetadataValues)
{
  // to hold the exiftool tag info
  double planckr1, planckr2, planckb, planckf, plancko;
  double tref, emis;
  double rawvaluemedian, rawvaluerange;

  // create our ExifTool object
  ExifTool *et = new ExifTool();

  // read metadata from the image
  TagInfo *info = et->ImageInfo(imgpath, NULL, 5);
  if (info) {
    // print returned information
    for (TagInfo *i=info; i; i=i->next) {
      std::string tagname = i->name;
	  
      if(!ci_find_substr( tagname, std::string("PlanckR1"))){
	//cout << tagname << " : " << i-> value << endl;
	planckr1 = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("PlanckR2"))){
	//cout << tagname << " : " << i-> value << endl;
	planckr2 = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("PlanckB"))){
	//cout << tagname << " : " << i-> value << endl;
        planckb = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("PlanckF"))){
	//cout << tagname << " : " << i-> value << endl;
	planckf = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("PlanckO"))){
	//cout << tagname << " : " << i-> value << endl;
	plancko = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("ReflectedApparentTemperature"))){
	//cout << tagname << " : " << i-> value << endl;
	tref = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("Emissivity"))){
	//cout << tagname << " : " << i-> value << endl;
	emis = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("RawValueMedian"))){
	//cout << tagname << " : " << i-> value << endl;
	rawvaluemedian = stod(i->value);
      } else if(!ci_find_substr( tagname, std::string("RawValueRange"))){
	//cout << tagname << " : " << i-> value << endl;
	rawvaluerange = stod(i->value);
      } else {
	//cout << tagname << " : " << i->value << endl;
      }
    }
    // we are responsible for deleting the information when done
    delete info;
  } else if (et->LastComplete() <= 0) {
    cerr << "Error executing exiftool!" << endl;
  }

  cout << "\n\n\nMetadata read .... " << endl;
  cout << "PlanckR1 : " << planckr1 << endl;
  cout << "PlanckR2 : " << planckr2 << endl;
  cout << "PlanckB : " << planckb << endl;
  cout << "PlanckF : " << planckf << endl;
  cout << "PlanckO : " << plancko << endl;
  cout << "Tref : " << tref << endl;
  cout << "Emis : " << emis << endl;
  cout << "RawValueMedian : " << rawvaluemedian << endl;
  cout << "RawValueRange : " << rawvaluerange << endl;
  
  thermalMetadata tdata(planckr1, planckr2,
			planckb, planckf, plancko,
			tref, emis,
			rawvaluemedian, rawvaluerange);
  thermalMetadataValues = tdata;
  
  // print exiftool stderr messages
  char *err = et->GetError();
  if (err) cerr << err;
  delete et;      // delete our ExifTool object

  //calculateTemperature(planckr1, planckr2,
  //       planckb, planckf, plancko,
  //		       tref, emis,
  //		       rawvaluemedian, rawvaluerange);
}


void CallBackFunc(int event, int x, int y, int flags, void* param)
{
    double          calculatedTemp;
    double          thermalvalue;

    const char*     imgpath;
    suitcase*       imgnpathdata;
    
    thermalMetadata tdata;
    Mat             rgb, thermalgray;

    
    if  ( event == EVENT_LBUTTONDOWN )
    {
      cout << "Left button of the mouse is clicked "
	   <<"- position "
	   <<" ("<< x << ", "
	   << y << ")"
	   << endl;
      imgnpathdata = (suitcase*) param;

      rgb          = imgnpathdata->img;
      thermalgray  = imgnpathdata->thermalimg;
      tdata        = imgnpathdata->tdata;
      imgpath      = imgnpathdata->imgpath;

      thermalvalue = (int)(thermalgray).at<Vec3b>(y, x)[0];
      calculatedTemp = tdata.calculateTemperature(thermalvalue);

      printf("%d %d: %d, %d, %d : %d %d %d : ( %d degrees)\n", 
                x, y, 
                (int)(rgb).at<Vec3b>(y, x)[0], 
                (int)(rgb).at<Vec3b>(y, x)[1], 
         	(int)(rgb).at<Vec3b>(y, x)[2],
        	(int)(thermalgray).at<Vec3b>(y, x)[0], 
                (int)(thermalgray).at<Vec3b>(y, x)[1], 
        	(int)(thermalgray).at<Vec3b>(y, x)[2],
        	(int)(calculatedTemp));

	
    }
    else if  ( event == EVENT_RBUTTONDOWN )
    {
      //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == EVENT_MBUTTONDOWN )
    {
      //cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if ( event == EVENT_MOUSEMOVE )
    {
      //cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }    
}



void readImage(const char* imgpath, Mat &imgmat, std::string customerrmsg)
{
    // read image from file 
    imgmat = imread(imgpath);
 
    // if fail to read the image
    if ( imgmat.empty() ) 
    { 
      cout << customerrmsg << imgpath << endl;
    }

}

 
int main()
{
    const char* rgbimgpath = "/home/eicossa/Dropbox/nabtd-images/FLIR1097-8/FLIR1097.jpg";
    std::string thermdataimgpath="";

    Mat rgbimg, thermalimg;

    readImage(rgbimgpath, rgbimg, "problem loading original FLIR image");
    
     // create a window
    namedWindow("AJRthermal", 1);

    // asdf
    thermalMetadata thermalMetadataValues;
    readExiftoolMetadata(rgbimgpath, thermalMetadataValues);

    // separate out the raw thermal data from the FLIR image
    extractRawThermaldata(rgbimgpath, thermdataimgpath);


    // read in the extracted thermal image bruh
    readImage(thermdataimgpath.c_str(), thermalimg, "problem loading thermal image");

    
    // perform calculations on thermal metadata bruh
    thermalMetadataValues.calculateRaws();
    thermalMetadataValues.calculateMaxMinTemperatures();
    thermalMetadataValues.printConsts();
    thermalMetadataValues.printRaws();
    thermalMetadataValues.printMaxMinTemps();

    suitcase imgnpathdata(rgbimg, rgbimgpath, thermalimg, thermdataimgpath.c_str(), thermalMetadataValues);
    
    //set the callback function for any mouse event
    setMouseCallback("AJRthermal", CallBackFunc, &imgnpathdata);
    
    //show the image
    imshow("AJRthermal", rgbimg);
 
    //Wait until user press some key
    waitKey(0);
   

    return 0;
}
