#include "../inc/flirImg.hpp"
#include "../inc/flirImgMetadata.hpp"

flirImg::flirImg(std::string imgpath)
{
  flirImgMetadata fmd(imgpath);


}

void flirImg::printImageSummary()
{
  fmd.printImageSummary();
}


// void flirImg::extractRawThermaldata()
// {
//   //rawthermdataimagename   = imgpath + std::string(".rawthermout.png");
//   std::string output;
//   std::string fullstring;

//   cout << "extracting raw thermal data";
  
//   fullstring = extractThermalCmdString()
//                +
//                std::string(" | ")
//                +
//                convert2Grayscale16bitCmdString()
//                +
//                getTHERMimgpath();
//   cout << fullstring;
  
  
//   output = exec(fullstring);
//   cout << output << endl;
//   //rawthermdataimgpath = rawthermdataimagename.c_str();
// }



// double flirImg::calcTempForOnePixel(double thermalintensityvalue)
// {
//   //calcEverything();
//   checkPlancks();
//   checkSmin();
//   checkSdelta();

//   double t61, t62, t63, t64, t65, t66, t67;
//   // just linearly mapped the thermal intensity values to a value between
//   // rawminobj and rawmaxobj using
//   // https://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another

//   //cout << "ThermalIntensityValue " << thermalintensityvalue;
//   t61 = rawminobj + ((rawmaxobj-rawminobj)/(65535))*(thermalintensityvalue);
//   // cout << "t61 : " << t61 << endl;
//   //t61 = 13900;
//   t62 = t61 + plancko;
//   t63 = planckr2 * t62;
//   t64 = (planckr1/t63) + planckf;
//   //t65 = planckb/log(t64) - smin;
//   t65 = planckb/log(t64);
//   //t66 = t65/sdelta;
//   t66 = t65 - 273.15;

//   return t66;
// }



// void flirImg::readRGBImage()
// {
//     // read image from file 
//     opencvimg = imread(getRGBimgpath());
 
//     // if fail to read the image
//     if ( opencvimg.empty() ) { 
//       cout << getRGBimgErrorMsg() << getRGBimgpath() << endl;
//       exit;
//     } else{
//       cout << "Successfully read in "
// 	   << getRGBimgpath() << endl;
//     }
    
//     //return opencvimg;
// }

// void flirImg::readThermalImage()
// {
//     // read image from file 
//     thermimg = imread(getTHERMimgpath(), IMREAD_ANYDEPTH);
 
//     // if fail to read the image
//     if ( thermimg.empty() ) { 
//       cout << getThermalimgErrorMsg() << getTHERMimgpath() << endl;
//       exit;
//     } else{
//       cout << "Successfully read in "
// 	   << getTHERMimgpath() << endl;
//     }
    
//     //return thermimg;
// }

// // this is a diagnostic thang
// void flirImg::writeThermalImageAsDiagnostic()
// {
//     // read image from file 
//     // thermimg = imread(getTHERMimgpath(), IMREAD_ANYDEPTH);

//   try{
//     imwrite(getTHERMimgDiagnosticpath(), thermimg);
//   }
//   catch(runtime_error& ex){
//     cout << ex.what() << endl;
//   }
//   cout << "Successfully wrote out diagnostic thermal image "
//        << getTHERMimgDiagnosticpath() << endl;


// }

// void flirImg::readPHPImage()
// {
//     // // read image from file 
//     // phpimg = imread(getPHPimgpath());
 
//     // // if fail to read the image
//     // if ( phpimg.empty() ) { 
//     //   cout << getPHPimgErrorMsg() << getPHPimgpath() << endl;
//     //   exit;
//     // } else{
//     //   cout << "Successfully read in "
//     // 	   << getPHPimgpath() << endl;
//     // }
    
//     // //return thermimg;
// }

// void printPixelDiagnostics(int coord_x, int coord_y,
// 			   int thermalintensityvalue,
// 			   double calculatedTemp)
// {
//   cout << setw(5)
//        <<" ("
//        << coord_x << ", "
//        << coord_y << ")  "
//        << "[ "        << thermalintensityvalue    << " ]"
//        << "[ Temp : " << calculatedTemp << " ]"
//        << endl;
// }

// void print50PixelsDiagnostics(flirImg* flirImgParam)
// {
//   Mat thermmat = flirImgParam->getThermImgMat();
//   int thermalvalue;
//   double calculatedTemp;
  
//   int j=24;
//   for(int i=200; i<=250; i++){
//     thermalvalue = (int)((thermmat).at<unsigned short>(j, i));
//     //cout << thermalvalue << endl;
//     calculatedTemp = flirImgParam->calcTemp(thermalvalue);
//     printPixelDiagnostics(i, j, thermalvalue, calculatedTemp);
//   }

// }



