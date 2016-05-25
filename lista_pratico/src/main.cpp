#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include "Point2D.hpp"
#include "Raster.hpp"

using namespace ivan94;
using namespace std;

int main(int argc, char const *argv[]) {
    if(argc != 8){
        printf("Not enough mana, I mean, arguments\n");
        return 0;
    }

    int height = atoi(argv[6]);
    int width = atoi(argv[5]);
    ofstream file(argv[7], ios::binary);

    Point2D p0(atoi(argv[1]), atoi(argv[2]));
    Point2D p1(atoi(argv[3]), atoi(argv[4]));

    vector<Point2D>* points = bresenhamLine(p0, p1);

    char img[height][width*3];

    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < 3*width; col++) {
            img[row][col] = 255;
        }
    }

    for (vector<Point2D>::iterator it = points->begin(); it!=points->end(); it++) {
        img[(*it).getY()][3*(*it).getX()+1] = 0;
        img[(*it).getY()][3*(*it).getX()+2] = 0;
    }

    char header[50];
    sprintf(header, "P6 %s %s 255 ", argv[5], argv[6]);
    file.write(header, strlen(header));

    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < 3*width; col++) {
            file.write(&img[row][col], 1);
        }
    }

    delete points;

    return 0;
}
