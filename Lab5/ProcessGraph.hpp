#pragma once
#include <TravelingPoint.hpp>
#include <VisualGraph.hpp>

class ProcessGraph : public VisualGraph {
	friend class TravelingPoint;
private:
	std::set<TravelingPoint*> m_points; 
	GLuint travelingBuffer;

protected:
	virtual void paintGL() override;
	virtual void generateBuffers() override;
	virtual void linkPrograms() override;

	virtual void drawTravelings();
	virtual float* generateTravelings();

	virtual void mouseReleaseEvent(QMouseEvent* ev) override;
	virtual void middleMouseButtonClick(Point mousePos, QMouseEvent* ev);

public:
	ProcessGraph(QWidget* parent = 0) : VisualGraph(parent) {};
};