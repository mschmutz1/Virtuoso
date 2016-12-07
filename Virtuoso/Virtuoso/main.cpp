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
#include "other.hpp"

using namespace cv;
using namespace std;

CascadeClassifier face_cascade;

int xmax = 179;
int ymax = 255;
int values_per_bins = 4;
int channels[2] = {0,1};
bool HSV = true;
int num_calibrating_frames = 10;
int frames_tracked = 4;
Point* previous_right;
Point* previous_left;
int count = 0;
int min_velocity = -10;
double percentageOfMax = .9;
Mat erode_element, dilate_element;


Point Calc_Velocity(Point location,int frame_num, int stick);
int Calc_Radius(Mat bin_image, Point Max);


int main(){

    //set up display window
    const string WinName ="Virtuoso";
    const string WinName2 = "Left Stick";
    const string WinName3 = "Right Stick";
    const string WinName4 = "In range";
    
    //set up timer for measuring frame rate
    clock_t start,start_frame;
    double duration, frame_per_sec;
    
    //initiate Mat objects
    Mat RGB_image, hsv_image, bin_image_right, bin_image_left,hsv_left,hsv_right,left_stick,right_stick,image, skin;
    MatND total_hist_right,total_hist_left, back_project;
    total_hist_right = Mat::zeros(xmax/values_per_bins, ymax/values_per_bins, CV_32FC1);
    total_hist_left = Mat::zeros(xmax/values_per_bins, ymax/values_per_bins, CV_32FC1);
    int calibration_frames_left= 0;
    int calibration_frames_right = 0;
    
    
    //parameters for image processing that can be changed
    Mat erode_element = getStructuringElement(MORPH_RECT, Size(2, 2));
    Mat dilate_element = getStructuringElement(MORPH_RECT, Size(11, 11));
    
    //For ball tracking
    Point maxloc_left;
    Point maxloc_right;
    Point velocity_right;
    Point velocity_left;
    previous_right = new Point[frames_tracked];
    previous_left = new Point[frames_tracked];
    vector<Vec3f> circles_right;
    vector<Vec3f> circles_left;
    int count_left = 0;
    int count_right = 0;
    int radius_right;
    int radius_left;
    int key = -1;
    
    
    //For frame rate
    int frames_processed = 0;
    double pix_per_sec;

    //Create Windows
    namedWindow(WinName,1);
    namedWindow(WinName2,1);
    namedWindow(WinName3,1);
    namedWindow(WinName4,1);
    
    //Set up boxes for calibration
    const int BOX_WIDTH = 45;
    const int BOX_HEIGHT = 45;
    const int BOX_Y = 240;
    const int BOX_X = 120;

    Rect left_box(BOX_X - BOX_WIDTH/2,BOX_Y - BOX_HEIGHT/2,BOX_WIDTH,BOX_HEIGHT);
    Rect right_box((480 - BOX_X) - BOX_WIDTH/2,BOX_Y - BOX_HEIGHT/2,BOX_WIDTH,BOX_HEIGHT);
    
    //set up video and set camera resolution
    VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH,480);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,360);
    bool frame_read;
    
    if (!cap.isOpened())
    {
        cout << "Cam is not opened" << endl;
    }
    
    cout << "Started frame collection" << endl;
    //main loop, processes each frame
    
    start = clock();
    
    while(true)
    {
        start_frame = clock();
        frame_read = cap.read(RGB_image); //assigns mat image to raw webcam footage
        
        if (!frame_read){
            cout << "Frame can't be read" << endl;
            break;
        }
        
        flip(RGB_image,RGB_image,1);
        
        //Zero binary images
        bin_image_right = Mat::zeros(360,480,CV_8UC1);
        bin_image_left = Mat::zeros(360,480,CV_8UC1);
        
        //Convery RGB to hsv colorspace
        cvtColor(RGB_image, hsv_image, CV_BGR2HSV);
        hsv_left = hsv_image(left_box);
        hsv_right =  hsv_image(right_box);
        hsv_image.convertTo(hsv_image, CV_32FC1);
        
        //Use different colorspaces
        if (HSV == true)
        {
            image = hsv_image;
        }
        else
        {
            image = RGB_image;
        }
        

        //Draw hand boxes
        if(calibration_frames_left < num_calibrating_frames && calibration_frames_right < num_calibrating_frames)
        {
            Calibration_Left_Prompt(&RGB_image, left_box);
            Calibration_Right_Prompt(&RGB_image, right_box);
        }
        
        else if (calibration_frames_left < num_calibrating_frames)
        {
            Calibration_Left_Prompt(&RGB_image, left_box);
            hist_threshold(&image, &bin_image_right, total_hist_right, percentageOfMax);
            //calcBackProject( &hue, 1, 0, hist, backproj, &ranges, 1, true );
            erode(bin_image_right, bin_image_right, erode_element);
            dilate(bin_image_right, bin_image_right, dilate_element);
            blur(bin_image_right,bin_image_right,Point(15,15));
            minMaxLoc(bin_image_right, 0, 0, 0, &maxloc_right);
            
            HoughCircles(bin_image_right, circles_right, CV_HOUGH_GRADIENT, 2,1);
            cout << circles_right.size() << endl;
        
            imshow(WinName3,bin_image_right);
            
        }
        else if (calibration_frames_right < num_calibrating_frames)
        {
            Calibration_Right_Prompt(&RGB_image, right_box);
            Find_And_Process(&image,&bin_image_left,total_hist_left);
            minMaxLoc(bin_image_left, 0, 0, 0, &maxloc_left);
            imshow(WinName2,bin_image_left);
        }
        else
        {
            Find_And_Process(&image,&bin_image_right,total_hist_right);
            hist_threshold(&image, &bin_image_right, total_hist_right, percentageOfMax);
            
            erode(bin_image_right, bin_image_right, erode_element);
            dilate(bin_image_right, bin_image_right, dilate_element);
            blur(bin_image_right,bin_image_right,Point(15,15));
            minMaxLoc(bin_image_right, 0, 0, 0, &maxloc_right);
            
            Re_Calibrate_Prompt(&RGB_image);
            minMaxLoc(bin_image_left, 0, 0, 0, &maxloc_left);
            minMaxLoc(bin_image_right, 0, 0, 0, &maxloc_right);
            
            if (circles_right.size() == 1){
                cout << "Circle found" << endl;
                maxloc_right.x = circles_right[0][0];
                maxloc_right.y = circles_right[0][1];
                circle(RGB_image,maxloc_left,circles_right[0][2],Scalar(0, 255, 0), -1,8, 0);
            }
            
            imshow(WinName2,bin_image_left);
            imshow(WinName3,bin_image_right);
        }
        
        if (key == 'l' && calibration_frames_left < num_calibrating_frames)
        {
            calibration_frames_left++;
            total_hist_left = Add_To_Hist(hsv_left,total_hist_left);
        }
        else if (key == 'r' && calibration_frames_right < num_calibrating_frames)
        {
            calibration_frames_right++;
            total_hist_right = Add_To_Hist(hsv_right,total_hist_right);
        }
        
        Scalar low_thresh(0,100,0);
        Scalar high_tresh(255, 255, 255);
        inRange(hsv_image, low_thresh, high_tresh, skin);
        
        if (maxloc_left.x != 0 || maxloc_left.y != 0)
        {
            count_left++;
        
            //radius_left = Calc_Radius(bin_image_left,maxloc_left);
            circle(RGB_image,maxloc_left,15,Scalar(0, 255, 0), -1,8, 0);
            velocity_left = Calc_Velocity(maxloc_left,count_left,0);
            
            if ((velocity_left.y < -10) && (maxloc_left.y < 260) && (maxloc_left.x < 240))
            {
                putText(RGB_image, "Left instrument hit", cvPoint(30, 330), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            }
            else if ((velocity_left.y < -10) && (maxloc_left.y < 260) && (maxloc_right.x > 240))
            {
                putText(RGB_image, "Right instrument hit", cvPoint(30, 330), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            }
            

        }
        else{
            count_left = 0;
        }
        if (maxloc_right.x != 0 || maxloc_right.y != 0)
        {
            count_right++;
            /*
            radius_right = Calc_Radius(bin_image_right,maxloc_right);
            circle(RGB_image,maxloc_right,radius_right,Scalar(0, 255, 0), -1, 8, 0);
            velocity_right = Calc_Velocity(maxloc_right,count_right,1);
            if ((velocity_right.y < -10) && (maxloc_right.y < 260) && (maxloc_right.x > 240))
            {
                putText(RGB_image, "Right instrument hit", cvPoint(30, 330), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            }
            else if ((velocity_right.y < -10) && (maxloc_right.y < 260) && (maxloc_right.x < 240))
            {
                putText(RGB_image, "Left instrument hit", cvPoint(30, 330), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 255, 0), 1, CV_AA);
            }
             */
        }
        else{
            count_right = 0;
        }
         
        imshow(WinName,RGB_image);
        //imshow(WinName4,skin);
        key = waitKey(30);
        
        if (key == ' '){
            calibration_frames_left = 0;
            calibration_frames_right = 0;
        }
        
        else if (key == 'q')
        {
            break;
        }
        
        frame_per_sec = ((double) CLOCKS_PER_SEC)/(clock() - start_frame);
        frames_processed++;
    }
    
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "frames per second " << frames_processed/duration << endl;
    return 0;
}
int Calc_Radius(Mat bin_image, Point max)
{
    double tmp_radius, max_radius = 0;
    double x_dist,y_dist;
    int val;
    for (int i=0; i<bin_image.cols; i++){
        for (int j=0; j<bin_image.rows; j++){
            if (bin_image.at<uchar>(j,i) > 100)
            {
                val = bin_image.at<uchar>(j,i);
                x_dist = abs(max.x - i);
                y_dist = abs(max.y - j);
                tmp_radius = sqrt(x_dist*x_dist + y_dist*y_dist);
                if (tmp_radius > max_radius)
                {
                    max_radius = tmp_radius;
                }
            }
        }
    }
    cout << max_radius << endl;
    return (int)max_radius;
}

/*
if (maxloc_left.x != 0 || maxloc_left.y != 0)
{
    
    previous_left[count_left%4] = maxloc_left;
    count_left++;
    Point total = Point(0,0);
    for (int i = 0; i<smoothing_value; i++){
        total.x += previous_left[i].x;
        total.y += previous_left[i].y;
    }
    total.x = total.x/smoothing_value;
    total.y = total.y/smoothing_value;
    
    circle(RGB_image,total,15,Scalar(0, 255, 0), -1, 8, 0);
}
else{
    previous_left[count_left%4] = previous_left[(count_left-1)%4];
    count_left++;
}
if (maxloc_right.x != 0 || maxloc_right.y != 0)
{
    previous_right[count_right%4] = maxloc_right;
    count_right++;
    Point total = Point(0,0);
    for (int i = 0; i<smoothing_value; i++){
        total.x += previous_right[i].x;
        total.y += previous_right[i].y;
    }
    total.x = total.x/smoothing_value;
    total.y = total.y/smoothing_value;
    
    circle(RGB_image,total,15,Scalar(0, 255, 0), -1, 8, 0);
}
else{
    previous_right[count_right%4] = previous_right[(count_right-1)%4];
    count_right++;
}

*/
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
