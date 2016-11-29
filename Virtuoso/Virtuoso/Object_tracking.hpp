//
//  Object_tracking.hpp
//  Virtuoso
//
//  Created by Mathias on 11/28/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#ifndef Object_tracking_hpp
#define Object_tracking_hpp

#include <stdio.h>
#include "global.h"

using namespace std;
using namespace cv;



Point Calc_Velocity(Point location,int frame_num, int stick);

#endif /* Object_tracking_hpp */
