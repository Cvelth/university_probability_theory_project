#pragma once

class Point {
private:
	float m_x, m_y;
	const float POINT_SIZE = 0.05f;

public:
	Point(float x = 0.f, float y = 0.f) : m_x(x), m_y(y) {};
	float x() { return m_x; }
	float y() { return m_y; }
	void x(float x) { m_x = x; }
	void y(float y) { m_y = y; }

	bool operator==(const Point& p);
	Point operator+(const Point& p);
	Point operator+=(const Point& p);
	Point operator-(const Point& p);
	Point operator=(const Point& p);

	Point operator*(float f);
	Point operator/(float f);

	static Point center(Point, Point);
	float length();
	Point normalize();
	Point perpendicular();
};