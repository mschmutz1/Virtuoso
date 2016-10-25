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
#include "findfaces.hpp"

using namespace cv;
using namespace std;

string Name ="Virtuoso";
string Name2 = "Original";

//callback functions
void onTrackbarMinR(int pos,void* userdata);
void onTrackbarMaxR(int pos,void* userdata);
void onTrackbarMaxG(int pos,void* userdata);
void onTrackbarMinG(int pos,void* userdata);
void onTrackbarMaxB(int pos,void* userdata);
void onTrackbarMinB(int pos,void* userdata);

int main(){
    
    VideoCapture cap(0);
    
    if (!cap.isOpened())
    {
        cout << "Cam is not opened" << endl;
    }
        
    int count = 0;
    
    
    namedWindow(Name,1);
    
    Mat image, gray, thresholdedImage;
    bool frame_read;
    
    /*
    int MinR = 70;
    int MinG = 74;
    int MinB = 80;
    int MaxR = 150;
    int MaxG = 150;
    int MaxB = 150;
    */

    int MinR = 70;
    int MinG = 74;
    int MinB = 80;
    int MaxR = 150;
    int MaxG = 150;
    int MaxB = 150;
    
    createTrackbar("MinR", Name, &MinR, 255, onTrackbarMinR, &MinR);
    createTrackbar("MaxR", Name, &MaxR, 255, onTrackbarMaxR, &MaxR);
    createTrackbar("MinG", Name, &MinG, 255, onTrackbarMinG, &MinG);
    createTrackbar("MaxG", Name, &MaxG, 255, onTrackbarMaxG, &MaxG);
    createTrackbar("MinB", Name, &MinB, 255, onTrackbarMinB, &MinB);
    createTrackbar("MaxB", Name, &MaxB, 255, onTrackbarMaxB, &MaxB);
    
    
    while(true){
       
        frame_read = cap.read(image); //assigns mat image to raw webcam footage
        
        if (!frame_read){
            cout << "Frame can't be read" << endl;
            break;
        }
        
        //cvtColor(image, HSVimage,CV_BGR2HSV);
        Scalar Dark_color = Scalar(MinB,MinG,MinR);
        Scalar Light_color = Scalar(MaxB,MaxG,MaxR);
        
        inRange(image,Dark_color,Light_color,thresholdedImage);
        
        cvtColor(image, gray, CV_BGR2GRAY);
        
        
        
        imshow(Name,image);
        
        if (waitKey(200)>0){
            break;
        }
        count++;
    }
    
    return 0;
}

void onTrackbarMinR(int pos,void* userdata){
    pos = getTrackbarPos("MinR", Name);
    *((int*)&userdata) = pos;
    cout << "Min R is now " << pos << endl;
}

void onTrackbarMaxR(int pos,void* userdata){
    pos = getTrackbarPos("MaxR", Name);
    *((int*)&userdata) = pos;
    cout << "Max R is now " << pos << endl;
}

void onTrackbarMaxG(int pos,void* userdata){
    pos = getTrackbarPos("MaxG", Name);
    *((int*)&userdata) = pos;
    cout << "Max G is now " << pos << endl;
}

void onTrackbarMinG(int pos,void* userdata){
    pos = getTrackbarPos("MinG", Name);
    *((int*)&userdata) = pos;
    cout << "Min G is now " << pos << endl;
}

void onTrackbarMaxB(int pos,void* userdata){
    pos = getTrackbarPos("MaxB", Name);
    *((int*)&userdata) = pos;
    cout << "Max B is now " << pos << endl;
}

void onTrackbarMinB(int pos,void*  userdata){
    pos = getTrackbarPos("MinB", Name);
    *((int*)&userdata) = pos;
    cout << "Min B is now " << pos << endl;
}