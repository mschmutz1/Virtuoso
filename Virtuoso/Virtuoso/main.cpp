//
//  main.cpp
//  Virtuoso
//
//  Created by Mathias on 10/14/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

int main(){
    
    VideoCapture cap(0);
    
    
    if (!cap.isOpened())
    {
        cout << "Cam is not opened" << endl;
    }
        
    int count = 0;
    
    while(count < 200){
        Mat image;
        Mat HSVimage;
        Mat thresholdedImage;
        
        int MinR;
        int MinG;
        int MinB;
        int MaxR;
        int MaxG;
        int MaxB;
        
        string Name ="Virtuoso";
        
        cv::createTrackbar("MinR", Name, &MinR, 255);
        cv::createTrackbar("MaxR", Name, &MaxR, 255);
        cv::createTrackbar("MinG", Name, &MinG, 255);
        cv::createTrackbar("MaxG", Name, &MaxG, 255);
        cv::createTrackbar("MinB", Name, &MinB, 255);
        cv::createTrackbar("MaxB", Name, &MaxB, 255);
        
        cap.read(image); //assigns mat  image to raw webcam footage

        //cvtColor(image, HSVimage,CV_BGR2HSV);
        Scalar Light_color = Scalar(MinB,MinG,MinR);
        Scalar Dark_color = Scalar(MaxB,MaxG,MaxR);
        
        inRange(image,Dark_color,Light_color,image);

        imshow(Name,image);
        count++;
    }
}