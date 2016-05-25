#ifndef __POINT2D_H
#define __POINT2D_H

namespace ivan94{
    class Point2D{
    private:
        int x, y;
    public:
        Point2D(int x, int y);

        int getX();
        void setX(int x);

        int getY();
        void setY(int y);
    };
}
#endif
