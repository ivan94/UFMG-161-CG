#include "Raster.hpp"
using namespace std;

namespace ivan94{
    vector<Point2D>* bresenhamLine(Point2D p0, Point2D p1){
        double dX = p1.getX() - p0.getX();
        double dY = p1.getY() - p0.getY();
        double error = -1.0;
        double deltaErr = dY/dX;
        int xInc, yInc;

        vector<Point2D>* points = new vector<Point2D>();

        if(dX > 0){
            xInc = 1;
        }else{
            xInc = -1;
        }

        if(dY > 0){
            yInc = 1;
        }else{
            yInc = -1;
        }

        if(deltaErr > 1.0 || deltaErr < -1.0){
            deltaErr = dX/dY;
            int x = p0.getX();
            for (int y = p0.getY(); yInc*y < yInc*p1.getY(); y+=yInc) {
                points->push_back(Point2D(x, y));
                error += xInc*yInc*deltaErr;
                if (error >= 0) {
                    x+=xInc;
                    error -= 1;
                }
            }

        }else{
            int y = p0.getY();
            for (int x = p0.getX(); xInc*x < xInc*p1.getX(); x+=xInc) {
                points->push_back(Point2D(x, y));
                error += xInc*yInc*deltaErr;
                if (error >= 0) {
                    y+=yInc;
                    error -= 1;
                }
            }
        }

        //
        points->push_back(p1);

        return points;
    }
}
