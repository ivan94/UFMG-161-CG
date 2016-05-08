#pragma once
#include "Color.h"


class Text{
private:
    int xPos, yPos;
    char* baseText;
    int value;
    Color color;

public:
    Text(int x, int y, char* baseText, Color color);
    void setValue(int value);
    int getValue();
    void draw();
};
