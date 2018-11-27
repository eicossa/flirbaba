/*
 * bezier.cpp
 * Source : https://github.com/thenatefisher/OpenCV-Beziers/blob/master/bezier.h
 * Bezier spline library for OpenCV (C++ only)
 * Author: Nate Fisher, nate.scott.fisher@gmail.com
 *
 */

#ifndef BEZIER_H
#define BEZIER_H

#include <stdio.h>
#include <cv.h>

using namespace cv;

class Bezier 
{
private:
  //Mat controlPoints;
  float **controlPoints;
  int numPoints;
  int precision;
  float **curvePoints;
public:
  Bezier();
  //Point getPoint(int t);
  //Point getControlPoint(int p);
  void setControlPoints(std::vector<Point> &input);
  
  int getLength();
  //void loadFile(char* filename[]);
  //void cvPlot();
  //IplImage cvImage();
  //void dumpPoints();
  std::vector<Point> calcDeCastelJauCurve();
  float* deCasteljau(float** points, int degree, float t);
};

#endif
