//
//  histogram.cpp
//  Virtuoso
//
//  Created by Mathias on 11/13/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#include <stdio.h>
#include "histogram.hpp"

using namespace cv;
using namespace std;

int maxB, maxG;
void hist_threshold(Mat* src_image, Mat* dest_image, MatND hist)
{
    Mat tmp_image;
    
    double maxVal;
    minMaxLoc(hist, 0, &maxVal, 0, 0);
    
   // cout << "max2: " << maxVal << endl;
    
    src_image->convertTo(tmp_image, CV_32FC1);
    for (int i = 0;i <src_image->rows; i++){
        for (int j = 0;j <src_image->cols; j++){
            Point3_<float>* p = tmp_image.ptr<Point3_<float>>(i,j);
            int B = (p->x);
            int G = (p->y);
            int B_index = B/4;
            int G_index = G/4;
            
            //cout << B << " " << G << " " << endl;
            
            {
                float binVal = hist.at<float>(B_index,G_index);

                if (binVal > .25*maxVal)
                {
                    dest_image->at<uchar>(i,j) = 255;
                    
                }
                else
                {
                    dest_image->at<uchar>(i,j) = 1;
                }
            }
        }
    }
}


MatND CreateHistHS(Mat* imag)
{
    // Quantize the hue to 30 levels
    // and the saturation to 32 levels
    int Bbins = 45, Gbins = 64;
    int histSize[] = {Bbins, Gbins};
    // hue varies from 0 to 179, see cvtColor
    float Branges[] = { 0, 179 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float Granges[] = { 0, 255 };
    const float* ranges[] = { Branges, Granges };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};
    
    calcHist(imag, 1, channels, Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false );
    /*
    //Rest is for debugging
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);
    
    cout << "max: " << maxVal << endl;
    
    int scale = 10;
    Mat histImg = Mat::zeros(Bbins*scale, Gbins*10, CV_8UC3);
    
    for( int B = 0; B < Bbins; B++ )
        for( int G = 0; G < Gbins; G++ )
        {
            float binVal = hist.at<float>(B, G);
            
            if (binVal == maxVal){
               maxB = B;
               maxG = G;
               cout << "HV: " << maxB << " " << maxG << endl;
            }
            int intensity = cvRound(binVal*255/maxVal);
            rectangle( histImg, Point(B*scale, G*scale),
                      Point((B+1)*scale - 1, (G+1)*scale - 1),
                      Scalar::all(intensity),
                      CV_FILLED );
        }
    
    namedWindow( "Cropped Face", 1 );
    imshow( "Cropped Face", *imag);
    
    namedWindow( "H-S Histogram", 1 );
    imshow( "H-S Histogram", histImg);
    //waitKey();
    */
    return hist;
};