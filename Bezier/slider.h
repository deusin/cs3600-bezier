#pragma once
#include <glm/glm.hpp>

class Slider
{
public:
	Slider(double x1, double y1, double x2, double y2, double r, double g, double b, double v);
	void Draw();
	bool Click(glm::vec2 clickPoint);
	double GetValue() { return mv; }
	void SetValue(double val) { mv = val; }
private:
	double mx1, my1, mx2, my2, mr, mg, mb, mv;
	void DrawRectangle(double x1, double y1, double x2, double y2);
};