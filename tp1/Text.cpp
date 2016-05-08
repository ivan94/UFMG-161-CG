#include <GLFW/glfw3.h>
#include <cstring>
#include <stdio.h>
#include "Text2D.h"
#include "Text.h"

Text::Text(int x, int y, char* baseText, Color color):
    xPos(x),
    yPos(y),
    baseText(baseText),
    color(color) {}

int Text::getValue(){
    return this->value;
}

void Text::setValue(int value){
    this->value = value;
}

void Text::draw(){
    char* str = new char[100];
    sprintf(str, baseText, value);
    glColor3f(color.getR(), color.getG(), color.getB());
    printText2D((const char*)str, xPos, yPos);
}
