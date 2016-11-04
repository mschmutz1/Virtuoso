//
//  main.cpp
//  Virtuoso
//
//  Created by Mathias on 10/14/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#include <iostream>
#include "stdio.h"
#include "global.h"
#include "DetectAndDrawFaces.hpp"

using namespace cv;
using namespace std;

int main(){
    //set up display window
    const string WinName ="Virtuoso";
    //set up timer for measuring frame rate
    clock_t start;
    double duration;
    start = clock();

    //set up video
    VideoCapture cap(0);
    Mat image, gray, thresholdedImage;
    
    //set camera resolution
    cap.set(CV_CAP_PROP_FRAME_WIDTH,480);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,360);
    
     //load classifier to look for faces
    const string face_cascade_name = "/Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/data/haarcascades/haarcascade_frontalface_alt.xml";
    CascadeClassifier face_cascade;
    face_cascade.load(face_cascade_name);
    
    if (!cap.isOpened())
    {
        cout << "Cam is not opened" << endl;
    }
        
    int frames_processed = 0;
    namedWindow(WinName,1);
    vector<Rect> faces;
    bool frame_read;

    cout << "Started frame collection" << endl;
    
    //main loop, processes each frame
    while(true){
        
        frame_read = cap.read(image); //assigns mat image to raw webcam footage
        
        if (!frame_read){
            cout << "Frame can't be read" << endl;
            break;
        }

        faces = DetectAndDrawFaces(&image,&face_cascade,true);
        
        imshow(WinName,image);
        
        if (waitKey(10)>0){
            break;
        }
        frames_processed++;
    }
    
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "frames per second " << frames_processed/duration << endl;
    return 0;
}

//Thresholding code

/*cvtColor(image, HSVimage,CV_BGR2HSV);
 Scalar Dark_color = Scalar(MinB,MinG,MinR);
 Scalar Light_color = Scalar(MaxB,MaxG,MaxR);
 
 inRange(image,Dark_color,Light_color,thresholdedImage);
 */

//Trackpad callbacks
/*
 void onTrackbarMinR(int pos,void* userdata);
 void onTrackbarMaxR(int pos,void* userdata);
 void onTrackbarMaxG(int pos,void* userdata);
 void onTrackbarMinG(int pos,void* userdata);
 void onTrackbarMaxB(int pos,void* userdata);
 void onTrackbarMinB(int pos,void* userdata);
 */

/*
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
 */

/*
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
*/

/*
 // Set Region of Interest
 cv::Rect roi_b;
 cv::Rect roi_c;
 
 size_t ic = 0; // ic is index of current element
 int ac = 0; // ac is area of current element
 
 size_t ib = 0; // ib is index of biggest element
 int ab = 0; // ab is area of biggest element
 
 
 
 for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)
 
 {
 cout << "Found face" << endl;
 
 roi_c.x = faces[ic].x;
 roi_c.y = faces[ic].y;
 roi_c.width = (faces[ic].width);
 roi_c.height = (faces[ic].height);
 
 ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)
 
 roi_b.x = faces[ib].x;
 roi_b.y = faces[ib].y;
 roi_b.width = (faces[ib].width);
 roi_b.height = (faces[ib].height);
 
 ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element
 
 if (ac > ab)
 {
 ib = ic;
 roi_b.x = faces[ib].x;
 roi_b.y = faces[ib].y;
 roi_b.width = (faces[ib].width);
 roi_b.height = (faces[ib].height);
 }
 
 crop = frame(roi_b);
 resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
 cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale
 
 // Form a filename
 
 filename = "";
 stringstream ssfn;
 ssfn << filenumber << ".png";
 filename = ssfn.str();
 filenumber++;
 
 imwrite(filename, gray);
 
 Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
 Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
 rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
 }
 
 // Show image
 sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
 text = sstm.str();
 
 putText(frame, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
 imshow("original", frame);
 
 if (!crop.empty())
 {
 imshow("detected", crop);
 }
 else
 destroyWindow("detected");
*/