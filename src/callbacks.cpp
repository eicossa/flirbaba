#include "../inc/callbacks.hpp"




// /*************************************************************************
//  *
//  *
//  ************************************************************************/


// /************************************************************************
//  *
//  *
//  ***********************************************************************/

// static Point       bezier_another_p;
// static Point       bezier_start_p;
// static Mat         bezier_thermimage_copy;
// static bool        bezier_drawing;
// std::vector<Point> beziercurve_pts;

// void drawSelectionBezierCurve(int event, int x, int y, int flags, void* param)
// {  
//   flirImg*       flirImgParam;
//   Mat            thermimage;
//   flirImgParam    = (flirImg*) param;
//   thermimage      = flirImgParam->getThermImgMat();

//   if ( event == EVENT_RBUTTONDOWN ){
//     bezier_drawing = false;
//     beziercurve_pts.clear();
//     imshow("ThermalBezierCurve", thermimage);
//   }
//   else if ( event == EVENT_LBUTTONDOWN ){
//     if(polyline_drawing){
//       bezier_another_p.x   = x;
//       bezier_another_p.y   = y;
//       beziercurve_pts.push_back(bezier_another_p);
//       if(bezier_drawing ){
//         bezier_thermimage_copy = thermimage.clone();
// 	Mat all_ps(beziercurve_pts);
// 	// check if atleasts points available
// 	// cv::drawContours();
// 	imshow("ThermalBezierCurve", bezier_thermimage_copy);
// 	bezier_thermimage_copy.release();
//       }
//     }
//     else{
//       polyline_drawing           = true;
//       polyline_start_p.x         = x;
//       polyline_start_p.y         = y;
//     }

//   }
//   else if ( event == EVENT_MOUSEMOVE){
//     //
//     //
//   }
//   else if ( event == EVENT_LBUTTONUP ){
//     //drawing = false;
//     //imshow("Thermal", thermimage);
//   }


// }




// static void displayImageWithTempsOnMouseover()
// {

// }

// static void displayImageWithRAWOnMouseover()
// {


// }

// static void displayImageWithCompleteCalcsOnMouseover()
// {


// }


// #include "../inc/flirImg.hpp"


// flirImg::flirImg()
// {
//   planckr1 = -1;
// }


// // #include "../inc/utilfunc.hpp"
// // using namespace std;


// // // find substring (case insensitive)
// // int ci_find_substr( const std::string& str1,
// // 		    const std::string& str2,
// // 		    const std::locale& loc)
// // {
// //     const_iterator it = std::search( str1.begin(), str1.end(), 
// //                                      str2.begin(), str2.end(),
// // 				     my_equal<typename T::value_type>(loc));
// //     if ( it != str1.end() ) return it - str1.begin();
// //     else return -1; // not found
// // }


