using namespace cv;

std::string getRGBimgpath()
{
  std::string path = "/home/eicossa/Dropbox/nabtd-images/FLIR1097-8/FLIR1097.jpg";
  return path;
}

std::string getTHERMimgpath()
{
  std::string path = getRGBimgpath() + ".thermout.png";
  return path;
}

std::string getRGBimgErrorMsg()
{
  std::string errmsg = "problem loading original FLIR img";
  return errmsg;
}

std::string getThermalimgErrorMsg()
{
  std::string errmsg = "problem loading thermal data from img";
  return errmsg;
}

std::string convert2GrayscaleCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - grayscale:- ");
  return cmdString;
}

std::string convert2Grayscale16bitCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - -depth 16 grayscale:- ");
  return cmdString;
}

std::string convert2GrayscaleMSBCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - -endian msb grayscale:- ");
  return cmdString;
}

std::string convert2GrayscaleAutolevelledCmdString()
{
  std::string cmdString;
  cmdString = std::string("convert - -auto-level grayscale:- ");
  return cmdString; 
}

std::string convertThermal2Grayscale16MSBAutolevelCmdString()
{
  std::string cmdString;
  cmdString = convert2GrayscaleCmdString()
            + std::string(" | ")
            + convert2Grayscale16bitCmdString()
            + std::string(" | ")
            + convert2GrayscaleMSBCmdString()
            + std::string(" | ")
            + convert2GrayscaleAutolevelledCmdString()
  return cmdString;

}

std::string extractThermalCmdString()
{
  std::string cmdString;
  cmdString = std::string("exiftool ")
              + getRGHimgpath()
              + std::string(" -rawthermalimage -b");
              + getTHERMimgpath();
  return cmdString;
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

void extractThermalImage()
{
  
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

