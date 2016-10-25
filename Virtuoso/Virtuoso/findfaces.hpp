//
//  findfaces.hpp
//  Virtuoso
//
//  Created by Mathias on 10/24/16.
//  Copyright © 2016 self.edu. All rights reserved.
//

#ifndef findfaces_hpp
#define findfaces_hpp

#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"


vector<Rect<int>> findfaces(Mat image);

#endif /* findfaces_hpp */
