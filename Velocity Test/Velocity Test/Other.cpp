//
//  Other.cpp
//  Virtuoso
//
//  Created by Mathias on 12/4/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#include "Other.hpp"



void Calibration_Left_Prompt(Mat* image, Rect box)
{
    putText(*image, "Press 'L' to Calibrate Left Stick", cvPoint(10, 300), FONT_HERSHEY_COMPLEX_SMALL, 0.5, cvScalar(0, 255, 0), 1, CV_AA);
    DrawShape(image,box);
}

void Calibration_Right_Prompt(Mat* image, Rect box)
{
    putText(*image, "Press 'R' to Calibrate Left Stick", cvPoint(250, 300), FONT_HERSHEY_COMPLEX_SMALL, 0.5, cvScalar(0, 255, 0), 1, CV_AA);
    DrawShape(image,box);
}

void Re_Calibrate_Prompt(Mat* image)
{
    putText(*image, "Press Space Bar to Re-Calibrate", cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
}