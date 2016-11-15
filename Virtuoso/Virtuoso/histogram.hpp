//
//  histogram.hpp
//  Virtuoso
//
//  Created by Mathias on 11/13/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#ifndef histogram_hpp
#define histogram_hpp

#include "global.h"

using namespace cv;
using namespace std;

MatND CreateHistHS(Mat* imag);

void hist_threshold(Mat* src_image, Mat* dest_image, MatND hist);

#endif /* histogram_hpp */
