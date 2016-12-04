//
//  DetectAndDrawFaces.cpp
//  Virtuoso
//
//  Created by Mathias on 10/24/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#include "DetectAndDrawFaces.hpp"

using namespace std;
using namespace cv;

extern CascadeClassifier face_cascade;

bool Calibrate_Hand(Mat& image,Rect box){
    bool hand_found = false;
    Mat frame = image(box);
    
    putText(image, "Calibrating", cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    
    vector<Rect> left_hand = DetectAndDrawFaces(&frame,&face_cascade,true);
    
    if (left_hand.size() == 1)
    {
        cout << "HAND FOUND" << endl;
        hand_found = true;
        
    }
    return hand_found;
}

/* See DetectAndDrawFaces.hpp for information*/
vector<Rect> DetectAndDrawFaces(Mat* frame, CascadeClassifier* face_cascade, bool draw)
{
    vector<Rect> faces;
    Mat frame_gray;
    cvtColor(*frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    
    // Detect faces
    face_cascade->detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(70,70));
    
    //cout << faces[0].x << " " << faces[0].y << " " << faces[0].width << " " << faces[0].height << " " << endl;
    
    if (faces.size() == 0)
    {
        putText(*frame, "No face detected", cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
        
    }
    else if (faces.size() > 1)
    {
        putText(*frame, "Too many faces detected", cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
        for (int i=0;i<faces.size();i++)
        {
            DrawShape(frame,faces[i]);
        }
    }
    
    else if (draw == true)
    {
        DrawShape(frame,faces[0]);
    }
    
    return faces;
}

void DrawShape(Mat* frame,Rect object)
{
    int x,y,width,height,radius;
    x = object.x;
    y = object.y;
    width = object.width;
    height = object.height;
    radius = width/2 * sqrt(2);
    //rectangle(*frame, Point(x,y), Point(x+width,y+height), Scalar(0, 255, 0), 2, 8, 0);
    circle(*frame,Point(x+width/2,y+height/2),radius,Scalar(0, 255, 0), 2, 8, 0);
}
