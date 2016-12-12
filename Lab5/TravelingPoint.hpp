#pragma once
#include <Graph.hpp>
#include <thread>
#include <random>

class ProcessGraph;
class DeadEndException {};

class TravelingPoint {
private:
	const float STEPS_PER_LINK = 25.f;
	const size_t STEP_TIME = 10;

	std::thread m_thread;

	std::mt19937_64* gen;
	std::uniform_real_distribution<float>* dist;

protected:
	Point m_coords;
	Point m_speed;
	float m_v;

	ProcessGraph* m_graph;

public:
	TravelingPoint(ProcessGraph* g, Node* n);
	~TravelingPoint();

	Point p() {	return m_coords; }
	float x() { return m_coords.x(); }
	float y() { return m_coords.y(); }
	float v() { return m_v; }
	
	void advance();
	void chooseNextPath(Node* n);
};