/*
 * bezier.cpp
 * Source : https://github.com/thenatefisher/OpenCV-Beziers/blob/master/bezier.cpp
 * Bezier spline library for OpenCV (C++ only)
 * Author: Nate Fisher, nate.scott.fisher@gmail.com
 *
 */

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <cv.h>
#include <fstream>

using namespace std;
#include "bezier.hpp"

/* 	Bezier() 
 * 	Constructor for Bezier object
*/
Bezier::Bezier(){}

/* 	setControlPoints() 
 * 	@input CvMat
 *	Loads the control points for a cubic Bezier
 */
void Bezier::setControlPoints(std::vector<Point> &input)
{
  this->numPoints     = input.size()-1;
  this->controlPoints = new float*[numPoints+1];
  
  for(int i=0; i<=numPoints; i++){
    Point w      = input.at(i);
    float *point = new float[3];

    cout << "Point " << i;
    
    point[0]     = (float)(w.x);
    cout << " 0 " << point[0] << " | ";
    
    point[1]     = (float)(w.y);
    cout << " 1 " << point[1] << " | ";
    
    point[2]     = 1.0;
    cout << " 2 " << point[2] << " | " << endl;

    controlPoints[i] = point;
  }
  
  this->precision     = 5;

}

/* 	getLength() 
*	Returns the number of control points in the spline as an integer
*/
int Bezier::getLength()
{
  return this->numPoints;
}

// /* 	getControlPoint() 
// *	@input int
// *	Returns a Point object with coordinates for a particular control point given by p
// */
// Point Bezier::getControlPoint(int p)
// {
//   Point output; 
//   //Mat spline = this->controlPoints; 	
//   std::vector<Point> spline = this->controlPoints;
//   output = spline.at(p);
//   //output.x = *((float*) spline[1][p]);
//   //output.y = *((float*) (*spline, 1, p) + spline->step);
  
//   return output;		
// }

// /* 	dumpPoints() 
// *
// *	Outputs all control points in spline to stdout
// */
// void Bezier::dumpPoints()
// {
//   cout << "why not coming here" << endl;
//   //Mat spline = this->controlPoints;
//   cout << "length : " << this->length << endl;

//   Point w;
//   for (int i = 1; i < this->length; i++){
//     w = this->controlPoints.at(i);
//     cout << "... X(" << i << "): " << w.x;
//     cout << " Y(" << i << "): " << w.y << endl;
//     //cout << "\tY: " << *((float*) (*spline, 1, i) + spline->step) << "\n";
//   }
// }

// /* 	loadFile() 
// *	@input char*
// *	Loads a text file with coordinates as float values, separated by commas
// *	Each point should be on a new line
// */
// void Bezier::loadFile(char* filename[])
// {

//   int lines = 1; 
//   float points[2][1000];
  
//   FILE* fp;
//   fp = fopen (*filename, "r");
//   fscanf(fp, "%f,%f", &points[0][0], &points[1][0]);
	
//   while(fscanf(fp, "%f,%f", &points[0][lines], &points[1][lines]) == 2)
//     lines++;
	
//   //close file
//   fclose(fp);
	
//   // set length property to number of control points
//   this->length = lines;
	
//   // create CvMat object
//   Mat input = Mat(lines, lines, CV_32FC2);
	
//   // load CvMat with coordinates
//   // this was originall *((float*) (*input, 1, i)+input->step) = points[1][i;]
//   for(int i = 0; i < lines; i++){
//     *((float*) (input, 1, i)) = points[0][i];
//     //*((float*) (*input, 1, i)+input->step) = points[1][i];
//   }
	
//   this->controlPoints = input;	
// }

// /* 	getPoint() 
// *	@input int
// *	Returns a Point object with coordinates for a particular station on the spline given by t
// */
// Point Bezier::getPoint(int t)
// {
//   cout << "... Getting Point with t = " << t << endl;
//   Point output;
//   std::vector<Point> spline = this->controlPoints; 	
  
//   int splineCount = this->length/4;
//   //cout << "Length : " << this->length << endl;
//   //cout << "SplineCount : " << splineCount << endl;
//   int currSpline  = (int) ((t/1000.0f) * (float) splineCount);
//   if (splineCount==0){
//     cout << "splineCount has become zero. Try again with more pts." << endl;
//     exit;
//   }
//   int splineShare = 1000/splineCount;
//   float step      = (t % splineShare) / (float)splineShare;
  
//   int CP[2][4];
//   // cout << "currSpline : " << currSpline
//   //      << "lower      : " << currSpline*4
//   //      << "upper      : " << (currSpline+1)*4
//   //      << endl;
  
//   Point w;
//   for (int i = currSpline*4; i < (currSpline+1)*4; i++){
//     //cout << "Trying to access element " << i << endl;
//     w        = spline.at(i);
    
//     CP[0][(i%4)] = (int)(w.x);
//     CP[1][(i%4)] = (int)(w.y);
//     //CP[0][i] = (int) *((float*) (*spline, 1, i));
//     //CP[1][i] = (int) *((float*) (*spline, 1, i) + spline->step);
//   }
	
//   int cx = 3 * (CP[0][1] - CP[0][0]);
//   int bx = 3 * (CP[0][2] - CP[0][1]) - cx;
//   int ax = CP[0][3] - CP[0][0] - cx - bx;
	
//   int cy = 3 * (CP[1][1] - CP[1][0]);
//   int by = 3 * (CP[1][2] - CP[1][1]) - cy;
//   int ay = CP[1][3] - CP[1][0] - cy - by;

//   output.x = (int) (ax*step*step*step + bx*step*step + cx*step + CP[0][0]);
//   output.y = (int) (ay*step*step*step + by*step*step + cy*step + CP[1][0]);
		
//   return output;
// }






std::vector<Point> Bezier::calcDeCastelJauCurve(){
  std::cout<< "newLine with numPoints : " << numPoints << " | " << endl;
  for(int j=0; j<= numPoints;j++){
    std:cout << controlPoints[j][0]
	     << ','
	     << controlPoints[j][1]
	     << ','
	     << controlPoints[j][2]
	     << endl;
  }
  
  curvePoints = new float*[precision+1];
  std::vector<Point> bezierContour;
  
  for(int i = 0; i <= precision; i++) {
    float u = float(i)/float(precision);
    curvePoints[i] = deCasteljau(controlPoints, numPoints, u);

    float* curvePoint = new float[3];
    curvePoint = curvePoints[i];
    
    cout << curvePoint[0] << ", "
	 << curvePoint[1] << ", "
	 << curvePoint[2] << " | "
	 << endl;
    Point newp((int)curvePoint[0], (int)curvePoint[1]);
    bezierContour.push_back(newp);
  }
  return bezierContour;

  
  // for(int i = 0; i <= precision; i++){
  //   float u = float(i)/float(precision);
  //   float *point = new float[3];
  //   point[0] = 0;
  //   point[1] = 0;
  //   point[2] = 0;
  //   for(int m = 0; m <= numPoints; m++){
  //     float bm = bernstein(m, numPoints, u);
  //     point[0] += bm * controlPoints[m][0];
  //     point[1] += bm * controlPoints[m][1];
  //     point[2] += bm * controlPoints[m][2];
  //   }
  //   curvePoints[i] = point;
  // }
  // by formula of Bezier curve
}


float* Bezier::deCasteljau(float** points, int degree, float t)
{
  float *pointsQ = new float[(degree + 1) * 3]; // same as pointsQ[numPoints + 1][3]
  int Qwidth = 3;
  for(int j = 0; j <= degree; j++){
    pointsQ[j*Qwidth + 0] = points[j][0];
    pointsQ[j*Qwidth + 1] = points[j][1];
    pointsQ[j*Qwidth + 2] = points[j][2];
  }
  for(int k = 1; k <= degree; k++){
    for(int j = 0; j<= degree - k; j++){
      pointsQ[j*Qwidth+0] = (1-t) * pointsQ[j*Qwidth+0] + t * pointsQ[(j+1)*Qwidth+0];
      pointsQ[j*Qwidth+1] = (1-t) * pointsQ[j*Qwidth+1] + t * pointsQ[(j+1)*Qwidth+1];
      pointsQ[j*Qwidth+2] = (1-t) * pointsQ[j*Qwidth+2] + t * pointsQ[(j+1)*Qwidth+2];
    }
  }
  float *result = new float[3];
  result[0] = pointsQ[0];
  result[1] = pointsQ[1];
  result[2] = pointsQ[2];
  delete[] pointsQ;
  return result;
}
