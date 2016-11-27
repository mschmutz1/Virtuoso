//
//  DetectAndDrawFaces.h
//  Virtuoso
//
//  Created by Mathias on 10/24/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#ifndef DetectAndDrawFaces_hpp
#define DetectAndDrawFaces_hpp

#include "global.h"

using namespace std;
using namespace cv;

bool Calibrate_Hand(Mat& image,Rect box);

//Performs histogram equilation on frame and find location/size of all faces using detectMultiScale
//frame - frame to be processed, passed by reference
//face_cascade - cascade classifier unique to opencv that holds information for object detection
//draw - boolean where true means draw squares around the faces on the frame and false means don't draw squares
//
//  returns vector of all faces coordinate information in Rect object
vector<Rect> DetectAndDrawFaces(Mat* frame, CascadeClassifier* face_cascade, bool draw);

void DrawShape(Mat* frame,Rect object);
#endif /* DetectAndDrawFaces_hpp */
