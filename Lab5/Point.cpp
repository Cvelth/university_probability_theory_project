#include <Point.hpp>
#include <ctgmath>

bool Point::operator==(const Point& p) {
	return fabs(m_x - p.m_x) < POINT_SIZE && fabs(m_y - p.m_y) < POINT_SIZE;
}

Point Point::operator+(const Point & p) {
	return Point(m_x + p.m_x, m_y + p.m_y);
}

Point Point::operator-(const Point & p) {
	return Point(m_x - p.m_x, m_y - p.m_y);
}

Point Point::operator=(const Point & p) {
	return Point(m_x = p.m_x, m_y = p.m_y);
}

Point Point::operator*(float f) {
	return Point(m_x * f, m_y * f);
}

Point Point::center(Point a, Point b) {
	return Point((a.m_x + b.m_x) / 2, (a.m_y + b.m_y) / 2);
}

float Point::length() {
	return sqrtf(m_x*m_x + m_y*m_y);
}

Point Point::normalize() {
	return Point(m_x / length(), m_y / length());
}

Point Point::perpendicular() {
	return Point(m_y, -m_x);
}
