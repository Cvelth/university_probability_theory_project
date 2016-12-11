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
	QMatrix4x4 projection;

	GLuint program;
	GLuint nodesBuffer;
	GLuint lineBuffer;

	GLuint opacityProgram;
	GLuint linksBuffer[2];

	float aspectRatio;
	Point lastMousePos;
	bool drawTempLine = false;

	const float NODE_SIZE = 0.04f;

protected:
	virtual void initializeGL() override {
		initializeOpenGLFunctions();
		glClearColor(0.1f, 0.f, 0.2f, 1.f);
		installShaders();

		glLineWidth(2.f);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &nodesBuffer);
		glGenBuffers(1, &lineBuffer);
		glGenBuffers(2, linksBuffer);
		
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

		glUseProgram(opacityProgram);
		drawLinks();

		glUseProgram(program);
		drawNodes();
		if (drawTempLine) {
			drawTempLink();
		}
	}

	virtual void drawNodes() {
		GLint projectionMatrix = glGetUniformLocation(program, "projectionMatrix");
		GLint drawingColor = glGetUniformLocation(program, "drawingColor");

		glBindBuffer(GL_ARRAY_BUFFER, nodesBuffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
		glUniform3f(drawingColor, 1.0f, 0.2f, 0.2f);

		glDrawArrays(GL_QUADS, 0, m_nodes.size() * 4);
	}
	virtual void drawTempLink() {
		GLint projectionMatrix = glGetUniformLocation(program, "projectionMatrix");
		GLint drawingColor = glGetUniformLocation(program, "drawingColor");

		glBindBuffer(GL_ARRAY_BUFFER, lineBuffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
		glUniform3f(drawingColor, 0.9f, 0.4f, 1.f);

		glDrawArrays(GL_LINES, 0, 4);

	}
	virtual void drawLinks() {
		GLint projectionMatrix = glGetUniformLocation(program, "projectionMatrix");
		GLint drawingColor = glGetUniformLocation(program, "drawingColor");

		//Lines
		glBindBuffer(GL_ARRAY_BUFFER, linksBuffer[0]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * (2 + 1), 0);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * (2 + 1), (void*) (sizeof(float) * 2));

		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
		glUniform3f(drawingColor, 0.7f, 0.4f, 1.f);

		glDrawArrays(GL_LINES, 0, m_links.size() * 2);

		//Arrows
		glBindBuffer(GL_ARRAY_BUFFER, linksBuffer[1]);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * (2 + 1), 0);
		glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * (2 + 1), (void*) (sizeof(float) * 2));

		glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
		glUniform3f(drawingColor, 0.7f, 0.4f, 1.f);

		glDrawArrays(GL_TRIANGLES, 0, m_links.size() * 3 * 2);

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
		glBindBuffer(GL_ARRAY_BUFFER, linksBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_links.size() * 2 * (2 + 1),
					 generateLinks(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, linksBuffer[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_links.size() * 3 * (2 + 1),
					 generateArrows(), GL_DYNAMIC_DRAW);
	}
	virtual void updatePosition(Point p) {
		glBindBuffer(GL_ARRAY_BUFFER, lineBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 2,
					 generateTempLink(p), GL_STREAM_DRAW);
	}

	void installShaders() {
		GLuint fragment = readShader(GL_FRAGMENT_SHADER, "FragmentShader.glsl");

		program = glCreateProgram();
		glAttachShader(program, readShader(GL_VERTEX_SHADER, "VertexShader.glsl"));
		glAttachShader(program, fragment);

		opacityProgram = glCreateProgram();
		glAttachShader(opacityProgram, readShader(GL_VERTEX_SHADER, "OpacityShader.glsl"));
		glAttachShader(opacityProgram, fragment);
			
		glLinkProgram(program);
		glLinkProgram(opacityProgram);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (!status)
			throw CompilationOrLinkingError();
		glGetProgramiv(opacityProgram, GL_LINK_STATUS, &status);
		if (!status)
			throw CompilationOrLinkingError();
	}
	GLuint readShader(GLenum type, std::string fileName) {
		GLuint shader = glCreateShader(type);
		const GLchar* temp[1];
		std::string s;
		s = readFile(fileName);
		temp[0] = s.c_str();
		glShaderSource(shader, 1, temp, 0);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (!status)
			throw CompilationOrLinkingError();

		return shader;
	}
	std::string readFile(std::string fileName) {
		return std::string(
			std::istreambuf_iterator<char>(std::ifstream(fileName)),
			std::istreambuf_iterator<char>()
		);
	}

	virtual float* generateNodes() {
		float* res = new float[m_nodes.size() * 2 * 4];
		size_t i = 0;
		for (Node* n : m_nodes)
			generateQuad(res, i, n, NODE_SIZE);
		return res;
	}
	virtual float* generateLinks() {
		float* res = new float[m_links.size() * 2 * (2 + 1)];
		size_t i = 0;
		for (Link* n : m_links)
			generateLine(res, i, n);
		return res;
	}
	virtual float* generateArrows() {
		float* res = new float[m_links.size() * 3 * (2 + 1)];
		size_t i = 0;
		for (Link* n : m_links)
			generateArrow(res, i, n);
		return res;
	}
	virtual float* generateTempLink(Point mousePos) {
		float* res = new float[4];
		size_t i = 0;
		generateLine(res, i, lastMousePos, mousePos);
		return res;
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
	void generateLine(float* place, size_t& index, Point start, Point end) {
		place[index++] = start.x();
		place[index++] = start.y();

		place[index++] = end.x();
		place[index++] = end.y();
	}
	void generateLine(float* place, size_t& index, Link* link) {
		place[index++] = link->b()->x();
		place[index++] = link->b()->y();
		place[index++] = link->v();

		place[index++] = link->e()->x();
		place[index++] = link->e()->y();
		place[index++] = link->v();
	}
	void generateArrow(float* place, size_t& index, Link* link) {
		Point start = link->b()->p();
		Point end = link->e()->p();
		Point center = Point::center(start, end);
		Point vector = end - start;
		Point perp = vector.perpendicular().normalize();
		Point left = center - perp * NODE_SIZE * 0.75f;
		Point right = center + perp * NODE_SIZE * 0.75f;

		Point front = center + vector.normalize() * NODE_SIZE * 1.5f;

		place[index++] = left.x();
		place[index++] = left.y();
		place[index++] = link->v();

		place[index++] = right.x();
		place[index++] = right.y();
		place[index++] = link->v();

		place[index++] = front.x();
		place[index++] = front.y();
		place[index++] = link->v();
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
						sendLinks();
					}
			}
		} else {
			if (e->button() == Qt::MouseButton::LeftButton) {
				Node* b = findNode(lastMousePos);
				Node* e = findNode(thisMousePos);
				if (b && e) {
					add(new Link(b, e));
					sendLinks();
				}
			} else if (e->button() == Qt::MouseButton::RightButton) {
				Link* l = findLink(lastMousePos, thisMousePos);
				if (l) {
					remove(l);
					sendLinks();
				}
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