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
  Mat* controlPoints;  
  int length;

public:
  Bezier();
  Point getPoint(int t);
  Point getControlPoint(int p);
  void setControlPoints(Mat* input);
  
  int getLength();
  void loadFile(char* filename[]);
  void cvPlot();
  IplImage cvImage();
  void dumpPoints();		
};

#endif
