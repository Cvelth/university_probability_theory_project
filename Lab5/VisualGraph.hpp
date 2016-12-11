#pragma once
#include <Graph.hpp>
#include <qopenglfunctions.h>
#include <fstream>
#include <QMatrix4x4>
#include <qvector4d.h>

class CompilationOrLinkingError {};

class VisualGraph 
	: public Graph, public QOpenGLWidget, private QOpenGLFunctions {
	friend class GraphWidget;
private:
	GLuint program;
	QMatrix4x4 projection;

	GLuint nodesBuffer;
	GLuint linksBuffer;
	GLuint arrowsBuffer;
	GLuint lineBuffer;

	float aspectRatio;
	Point lastMousePos;
	bool drawTempLine = false;

	const float NODE_SIZE = 0.04f;

protected:
	virtual void initializeGL() override {
		initializeOpenGLFunctions();
		glClearColor(1.f, 1.f, 1.f, 1.f);
		installShaders();

		glGenBuffers(1, &nodesBuffer);
		glEnableVertexAttribArray(0);
		glGenBuffers(1, &linksBuffer);
		glEnableVertexAttribArray(0);
		glGenBuffers(1, &arrowsBuffer);
		glEnableVertexAttribArray(0);
		glGenBuffers(1, &lineBuffer);
		glEnableVertexAttribArray(0);
		
		sendData();
	}

	virtual void resizeGL(int w, int h) {
		aspectRatio = float(w) / h;
		glViewport(0, 0, w, h);
		projection = QMatrix4x4();
		if (aspectRatio > 1.f)
			projection.ortho(-aspectRatio, +aspectRatio, -1.f, +1.f, -1.f, +1.f);
		else
			projection.ortho(-1.f, +1.f, -1.f / aspectRatio, +1.f / aspectRatio, -1.f, +1.f);
	}

	virtual void paintGL() override {
		glClear(GL_COLOR_BUFFER_BIT);
		GLint projectionMatrix, drawingColor;
		
		glUseProgram(program);
		projectionMatrix = glGetUniformLocation(program, "projectionMatrix");
		drawingColor = glGetUniformLocation(program, "drawingColor");


		//LINKS
		glBindBuffer(GL_ARRAY_BUFFER, linksBuffer);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
		glUniform3f(drawingColor, 0.f, 1.f, 0.f);

		glDrawArrays(GL_LINES, 0, m_links.size() * 2);

		//ARROWS
		glBindBuffer(GL_ARRAY_BUFFER, arrowsBuffer);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
		glUniform3f(drawingColor, 0.f, 1.f, 0.f);

		glDrawArrays(GL_TRIANGLES, 0, m_links.size() * 3 * 2);

		//NODES
		glBindBuffer(GL_ARRAY_BUFFER, nodesBuffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
		glUniform3f(drawingColor, 0.5f, 0.f, 0.5f);

		glDrawArrays(GL_QUADS, 0, m_nodes.size() * 4);

		//TEMP LINK
		if (drawTempLine) {
			glBindBuffer(GL_ARRAY_BUFFER, lineBuffer);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
			glUniform3f(drawingColor, 0.f, 0.5f, 0.f);

			glDrawArrays(GL_LINES, 0, 4);
		}
	}

	virtual void sendData() {
		sendNodes();
		sendLinks();
	}

	virtual void sendNodes() {
		glBindBuffer(GL_ARRAY_BUFFER, nodesBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_nodes.size() * 2 * 4,
					 generateNodes(), GL_DYNAMIC_DRAW);
	}

	virtual void sendLinks() {
		glBindBuffer(GL_ARRAY_BUFFER, linksBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_links.size() * 2 * 2,
					 generateLinks(), GL_DYNAMIC_DRAW);
	}

	virtual void sendArrows() {
		glBindBuffer(GL_ARRAY_BUFFER, arrowsBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_links.size() * 3 * 2,
					 generateArrows(), GL_DYNAMIC_DRAW);
	}

	virtual void updatePosition(Point p) {
		glBindBuffer(GL_ARRAY_BUFFER, lineBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 2,
					 generateTempLink(p), GL_STREAM_DRAW);
	}

	virtual void installShaders() {
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* temp[1];
		std::string s;

		program = glCreateProgram();
			
		s = readFile("VertexShader.glsl");
		temp[0] = s.c_str();
		glShaderSource(vertex, 1, temp, 0);
		glCompileShader(vertex);
		glAttachShader(program, vertex);

		s = readFile("FragmentShader.glsl");
		temp[0] = s.c_str();
		glShaderSource(fragment, 1, temp, 0);
		glCompileShader(fragment);
		glAttachShader(program, fragment);

		glLinkProgram(program);

		GLint tmp, status = 1;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &tmp);
		status &= tmp;
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &tmp);
		status &= tmp;
		glGetProgramiv(program, GL_LINK_STATUS, &tmp);
		status &= tmp;
		if (!status)
			throw CompilationOrLinkingError();
	}

	void generateQuad(float* place, size_t& index, Node* node, const float shift) {
		place[index++] = node->x() - shift;
		place[index++] = node->y();

		place[index++] = node->x();
		place[index++] = node->y() + shift;

		place[index++] = node->x() + shift;
		place[index++] = node->y();

		place[index++] = node->x();
		place[index++] = node->y() - shift;
	}

	void generateLine(float* place, size_t& index, Link* link) {
		generateLine(place, index, link->b()->p(), link->e()->p());
	}

	void generateLine(float* place, size_t& index, Point start, Point end) {
		place[index++] = start.x();
		place[index++] = start.y();

		place[index++] = end.x();
		place[index++] = end.y();
	}

	void generateArrow(float* place, size_t& index, Link* link) {
		generateArrow(place, index, link->b()->p(), link->e()->p());
	}

	void generateArrow(float* place, size_t& index, Point start, Point end) {
		Point center = Point::center(start, end);
		Point vector = end - start;
		Point perp = vector.perpendicular().normalize();
		Point left = center - perp * NODE_SIZE * 0.75f;
		Point right = center + perp * NODE_SIZE * 0.75f;

		Point front = center + vector.normalize() * NODE_SIZE * 1.5f;

		place[index++] = left.x();
		place[index++] = left.y();

		place[index++] = right.x();
		place[index++] = right.y();

		place[index++] = front.x();
		place[index++] = front.y();
	}

	float* generateNodes() {
		float* res = new float[m_nodes.size() * 2 * 4];
		size_t i = 0;
		for(Node* n : m_nodes) 
			generateQuad(res, i, n, NODE_SIZE);
		return res;
	}

	float* generateLinks() {
		float* res = new float[m_links.size() * 2 * 2];
		size_t i = 0;
		for (Link* n : m_links)
			generateLine(res, i, n);
		return res;
	}

	float* generateArrows() {
		float* res = new float[m_links.size() * 3 * 2];
		size_t i = 0;
		for (Link* n : m_links)
			generateArrow(res, i, n);
		return res;
	}

	float* generateTempLink(Point mousePos) {
		float* res = new float[4];
		size_t i = 0;
		generateLine(res, i, lastMousePos, mousePos);
		return res;
	}

	std::string readFile(std::string fileName) {
		return std::string(
			std::istreambuf_iterator<char>(std::ifstream(fileName)),
			std::istreambuf_iterator<char>()
		);
	}

	virtual void mousePressEvent(QMouseEvent* e) override {
		lastMousePos = translate(e->pos());
		drawTempLine = true;
	}
	virtual void mouseMoveEvent(QMouseEvent* e) override {
		updatePosition(translate(e->pos()));
		update();
	}

	virtual void mouseReleaseEvent(QMouseEvent* e) override {
		drawTempLine = false;
		Point thisMousePos = translate(e->pos());
		if (lastMousePos == thisMousePos) {
			if (e->button() == (Qt::MouseButton::LeftButton)) {
				if (!isNode(thisMousePos)) {
					add(new Node(thisMousePos));
					sendNodes();
				}
			} else {
				if (e->button() == (Qt::MouseButton::RightButton))
					if (isNode(thisMousePos)) {
						remove(findNode(thisMousePos));
						sendNodes();
					}
			}
		} else {
			if (e->button() == Qt::MouseButton::LeftButton) {
				Node* b = findNode(lastMousePos);
				Node* e = findNode(thisMousePos);
				if (b && e) {
					add(new Link(b, e));
					sendLinks();
					sendArrows();
				}

			} else if (e->button() == Qt::MouseButton::RightButton) {
			}
		}
		update();
	}

	Point translate(QPoint p) {
		QMatrix4x4 m;
		m.scale(2.f, 2.f, 1.f);
		if (aspectRatio > 1.f)
			m.translate(-aspectRatio / 2.f, 0.5f);
		else
			m.translate(-0.5f, +0.5f / aspectRatio);

		QVector4D v((float(p.x()) / width()), -(float(p.y()) / height()), 0.f, 1.f);
		v = m * projection.inverted() * v;
		return Point(v[0], v[1]);
	}

public:
	explicit VisualGraph(QWidget* parent = 0) 
		: QOpenGLWidget(parent) {};
};