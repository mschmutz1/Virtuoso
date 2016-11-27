//
//  main.cpp
//  Virtuoso
//
//  Created by Mathias on 10/14/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#include "global.h"
#include "DetectAndDrawFaces.hpp"
#include "histogram.hpp"
#include <stdlib.h> 

using namespace cv;
using namespace std;

CascadeClassifier face_cascade;

int main(){
    //set up display window
    const string WinName ="Virtuoso";
    const string WinName2 = "Skin";
    const string WinName3 = "Edges";
    
    //set up timer for measuring frame rate
    clock_t start;
    double duration;
    start = clock();

    //set up video
    VideoCapture cap(0);
    Mat image, hsv_image, hsv_left,hsv_right,cropped_face, skin_image, skin_left, skin_right, sobel;
    MatND total_hist;
    total_hist = Mat::zeros(45, 64, CV_32FC1);
    
    //For testing
    Mat hand_frames[5];
    
    
    MatND curr_hist;
    double percentageOfMax = .6;
    
    //set camera resolution
    cap.set(CV_CAP_PROP_FRAME_WIDTH,480);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,360);
    
     //load classifier to look for faces
    const string face_cascade_name = "/Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/data/haarcascades/haarcascade_hand.xml";
    
    face_cascade.load(face_cascade_name);
    
    Mat erode_element = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat dilate_element = getStructuringElement(MORPH_RECT, Size(7, 7));
    int lowThreshold = 10;
    int ratio = 3;
    int random_points = 40;
    
    if (!cap.isOpened())
    {
        cout << "Cam is not opened" << endl;
    }
        
    int frames_processed = 0;
    int left_hand_frames= 0;
    
    
    //Create Windows
    namedWindow(WinName,1);
    namedWindow(WinName2,1);
    //namedWindow(WinName3,1);
    //namedWindow("sobel",1);
    
    vector<Rect> left_hand;
    vector<Rect> right_hand;
    
    bool frame_read;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    const int BOX_WIDTH = 140;
    const int BOX_HEIGHT = 180;
    const int BOX_Y = 240;
    const int BOX_X = 120;

    Rect left_box(BOX_X - BOX_WIDTH/2,BOX_Y - BOX_HEIGHT/2,BOX_WIDTH,BOX_HEIGHT);
    Rect right_box((480 - BOX_X) - BOX_WIDTH/2,BOX_Y - BOX_HEIGHT/2,BOX_WIDTH,BOX_HEIGHT);
    
    cout << "Started frame collection" << endl;
    //main loop, processes each frame
    while(true){
        
        frame_read = cap.read(image); //assigns mat image to raw webcam footage
        flip(image,image,1);
        
        skin_image = Mat::zeros(360,480,CV_8UC1);
        cvtColor(image, hsv_image, CV_BGR2HSV);
        skin_left = skin_image(left_box);
        skin_right = skin_image(right_box);
        if (!frame_read){
            cout << "Frame can't be read" << endl;
            break;
        }
        
    
        hsv_image.convertTo(hsv_image, CV_32FC1);
        Point3_<float>* p = hsv_image.ptr<Point3_<float>>(10,10);
        cout << (int)p->x << " " << (int)p->y << endl;

        //Draw hand boxes
        DrawShape(&image,right_box);
        DrawShape(&image,left_box);
        
        //
        if (left_hand_frames < 5)
        {
            bool left_hand_found = Calibrate_Hand(image,left_box);
            
            if (left_hand_found)
            {
                left_hand_frames++;
                cropped_face = hsv_image(left_box);
                curr_hist = CreateHistHS(&cropped_face);
                total_hist = total_hist + curr_hist;
            }
                
        }
        else
        {
            putText(image, "Press 'R' to Re-Calibrate", cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
            hsv_left = hsv_image(left_box);
            hsv_right =  hsv_image(right_box);
            hist_threshold(&hsv_left, &skin_left, total_hist, percentageOfMax);
            hist_threshold(&hsv_right, &skin_right, total_hist, percentageOfMax);
            //Canny(skin_image, skin_image, lowThreshold,lowThreshold*ratio);
            imshow(WinName2,skin_image);
            
        }
        imshow(WinName,image);
        
        int key = waitKey(10);
        
        if (key == ' '){
            left_hand_frames = 0;
        }
        else if (key > 0)
        {
            break;
        }
        
        frames_processed++;
    }
    
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "frames per second " << frames_processed/duration << endl;
    return 0;
}

/*
 int H_total = 0;
 int S_total = 0;
 int V_total = 0;
 Rect small_face(x+width/4,y+height/4,width/2,height/2);
 
 
 hsv_image.convertTo(hsv_image, CV_32FC1);
 
 for (int i=0; i<random_points; i++){
 int point_x = rand() % small_face.width;
 int point_y = rand() % small_face.height;
 Point3_<float>* p = hsv_image.ptr<Point3_<float>>(small_face.x+point_x,small_face.y+point_y);
 int H = (p->x);
 int S = (p->y);
 int V = (p->z);
 H_total = H_total + H;
 S_total = S_total + S;
 V_total = V_total + V;
 }
 
 int H_avg = H_total/random_points;
 int S_avg = S_total/random_points;
 int V_avg = V_total/random_points;
 
 cout << H_avg << " " << S_avg << " " << V_avg << endl;
 
 Scalar low_thresh(H_avg - 40,  S_avg - 30, V_avg - 30);
 Scalar high_tresh(H_avg + 40, S_avg + 30, V_avg + 30);
 inRange(hsv_image, low_thresh, high_tresh, skin_image);
 */






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