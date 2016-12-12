#pragma once
#include <Graph.hpp>
#include <GUI.h>
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <QMatrix4x4>

class CompilationOrLinkingError {};

class VisualGraph 
	: public QOpenGLWidget, protected QOpenGLFunctions, public Graph {

	Q_OBJECT

	friend class GraphWidget;
private:
	GLuint nodesBuffer;
	GLuint lineBuffer;
	GLuint linksBuffer[2];

	float aspectRatio;

	WeightDialog* dialog;
	Link* currentLink;

protected:
	QMatrix4x4 projection;

	GLuint program;
	GLuint opacityProgram;

	Point lastMousePos;
	bool drawTempLine = false;

	const float NODE_SIZE = 0.04f;

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

	virtual void generateBuffers();
	virtual void linkPrograms();
	GLuint makeProgram(std::initializer_list<GLuint> shaders);
	GLuint readShader(GLenum type, std::string fileName);
	std::string readFile(std::string fileName);

	virtual void drawNodes();
	virtual void drawTempLink();
	virtual void drawLinks();

	virtual void sendData();
	virtual void sendNodes();
	virtual void sendLinks();
	virtual void updatePosition(Point p);

	virtual float* generateNodes();
	virtual float* generateLinks();
	virtual float* generateArrows();
	virtual float* generateTempLink(Point mousePos);

	void generateQuad(float* place, size_t& index, Node* node, const float shift);
	void generateQuad(float* place, size_t& index, Point point, const float shift);
	void generateLine(float* place, size_t& index, Point start, Point end);
	void generateLine(float* place, size_t& index, Link* link);
	void generateArrow(float* place, size_t& index, Link* link);
		
	virtual void mousePressEvent(QMouseEvent* e) override;
	virtual void mouseMoveEvent(QMouseEvent* e) override;
	virtual void mouseReleaseEvent(QMouseEvent* ev) override;

	virtual void leftMouseButtonClick (Point mousePos, QMouseEvent* ev);
	virtual void rightMouseButtonClick(Point mousePos, QMouseEvent* ev);
	virtual void leftMouseButtonSwipe (Point mousePos, QMouseEvent* ev);
	virtual void rightMouseButtonSwipe(Point mousePos, QMouseEvent* ev);

	Point translate(QPoint p);
public:
	explicit VisualGraph(QWidget* parent = 0);

signals:
	void showDialog(int, int);

protected slots:
	void changeLinkWeight(float value);
};