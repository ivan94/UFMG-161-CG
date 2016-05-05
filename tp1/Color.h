#pragma once
class Color {
private:
	float r, g, b;
public:
	Color(float r, float g, float b);
	float getR();
	float getG();
	float getB();

	static Color red();
	static Color green();
	static Color blue();
	static Color white();
};
