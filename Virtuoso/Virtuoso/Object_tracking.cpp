//
//  Object_tracking.cpp
//  Virtuoso
//
//  Created by Mathias on 11/28/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#include "Object_tracking.hpp"

using namespace std;
using namespace cv;

extern int frames_tracked;
extern Point* previous_right;
extern Point* previous_left;
extern int min_velocity;

Point Calc_Velocity(Point location,int frame_num, int stick)
{
    Point* velocity = new Point[frames_tracked - 1];
    Point* previous;
    Point avg = Point(0,0);
    if (stick == 1)
    {
        previous = previous_left;
    }
    else
    {
        previous = previous_right;
    }
    
    previous[frame_num%frames_tracked] = location;
    
    
    if (frame_num > frames_tracked){
        for (int i = 1; i<frames_tracked; i++)
        {
            velocity[i-1] = previous[i] - previous[i-1];
            avg.x += velocity[i-1].x;
            avg.y += velocity[i-1].y;
        }
        
        avg.x = avg.x/frames_tracked;
        avg.y = avg.y/frames_tracked;
        
        return avg;
    }
    
    return Point(0,0);
}

bool PlaySound(Point velocity, Point location)
{
    return false;
}
