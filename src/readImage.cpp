#include <string>

using namespace cv;
using namespace std;





void extractThermalImage()
{
  
}


Mat readRGBImage()
{
    // read image from file 
    imgmat = imread(getRGBimgpath());
 
    // if fail to read the image
    if ( imgmat.empty() ) 
    { 
      cout << getRGBimgErrorMsg() << imgpath << endl;
      exit;
    }
    return imgmat;
}


Mat readThermalImage()
{
  extractThermalImage();  
  exec(extractThermalCmdString());
}




void extractRawThermaldata(const char* imgpath, std::string &rawthermdataimagename)
{
  //rawthermdataimagename   = imgpath + std::string(".rawthermout.png");
  
  std::string output;
  output = exec(rawthermaldatacmdstring);
  cout << output << endl;
  //rawthermdataimgpath = rawthermdataimagename.c_str();
}





void readImageIntoWindow()
{
  namedWindow("AJRthermal", 1);
  imshow("AJRthermal", readRGBImage());

}

void readExifTags()
{
  exifTagdata exifTagValues;
  readExiftoolMetadata(rgbimgpath, exifTagValues);

}



void loadThermalData()
{
  // read in the extracted thermal image bruh
  readImage(thermdataimgpath.c_str(),
	    thermalimg,
	    "problem loading thermal image");
}
