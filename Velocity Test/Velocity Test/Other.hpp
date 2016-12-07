//
//  Other.hpp
//  Virtuoso
//
//  Created by Mathias on 12/4/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#ifndef Other_hpp
#define Other_hpp

#include "DetectAndDrawFaces.hpp"

#include <stdio.h>

using namespace cv;
using namespace std;

void Calibration_Left_Prompt(Mat* image, Rect box);
void Calibration_Right_Prompt(Mat* image, Rect box);
void Re_Calibrate_Prompt(Mat* image);

#endif /* Other_hpp */
