#include "Color.h"

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

float Color::getR() {
	return r;
}

float Color::getG() {
	return g;
}

float Color::getB() {
	return b;
}

Color Color::red() {
	return Color(1.0f, 0.0f, 0.0f);
}

Color Color::green() {
	return Color(0.0f, 1.0f, 0.0f);
}

Color Color::blue() {
	return Color(0.0f, 0.0f, 1.0f);
}

Color Color::white() {
	return Color(1.0f, 1.0f, 1.0f);
}