#pragma once
#include <Graph.hpp>
#include <GUI.h>
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <QMatrix4x4>

class CompilationOrLinkingError {};

class VisualGraph 
	: public QOpenGLWidget, private QOpenGLFunctions, public Graph {

	Q_OBJECT

	friend class GraphWidget;
private:
	QMatrix4x4 projection;

	GLuint program;
	GLuint nodesBuffer;
	GLuint lineBuffer;

	GLuint opacityProgram;
	GLuint linksBuffer[2];

	float aspectRatio;
	Point lastMousePos;
	bool drawTempLine = false;

	WeightDialog* dialog;
	Link* currentLink;

	const float NODE_SIZE = 0.04f;

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void drawNodes();
	virtual void drawTempLink();
	virtual void drawLinks();

	virtual void sendData();
	virtual void sendNodes();
	virtual void sendLinks();
	virtual void updatePosition(Point p);

	void installShaders();
	GLuint readShader(GLenum type, std::string fileName);
	std::string readFile(std::string fileName);

	virtual float* generateNodes();
	virtual float* generateLinks();
	virtual float* generateArrows();
	virtual float* generateTempLink(Point mousePos);

	void generateQuad(float* place, size_t& index, Node* node, const float shift);
	void generateLine(float* place, size_t& index, Point start, Point end);
	void generateLine(float* place, size_t& index, Link* link);
	void generateArrow(float* place, size_t& index, Link* link);
		
	virtual void mousePressEvent(QMouseEvent* e) override;
	virtual void mouseMoveEvent(QMouseEvent* e) override;
	virtual void mouseReleaseEvent(QMouseEvent* ev) override;

	Point translate(QPoint p);
public:
	explicit VisualGraph(QWidget* parent = 0);

signals:
	void showDialog(int, int);

protected slots:
	void changeLinkWeight(float value);
};