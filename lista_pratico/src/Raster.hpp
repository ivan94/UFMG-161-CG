#ifndef __RASTER_H
#define __RASTER_H

#include <vector>
#include "Point2D.hpp"
using namespace std;

namespace ivan94{
    vector<Point2D>* bresenhamLine(Point2D p0, Point2D p1);
}

#endif
