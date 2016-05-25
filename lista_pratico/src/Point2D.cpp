#include "Point2D.hpp"


namespace ivan94{
    Point2D::Point2D(int x, int y){
        this->x = x;
        this->y = y;
    }

    int Point2D::getX(){
        return x;
    }

    int Point2D::getY(){
        return y;
    }

    void Point2D::setX(int x){
        this->x = x;
    }

    void Point2D::setY(int y){
        this->y = y;
    }
}
