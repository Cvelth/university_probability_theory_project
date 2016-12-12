#include "ProcessGraph.hpp"
#include <QtWidgets>

void ProcessGraph::paintGL() {
	VisualGraph::paintGL();

	glUseProgram(program);
	glBindBuffer(GL_ARRAY_BUFFER, travelingBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_points.size() * 4 * (2 + 0),
				 generateTravelings(), GL_STREAM_DRAW);
	drawTravelings();
}
void ProcessGraph::generateBuffers() {
	VisualGraph::generateBuffers();
	glGenBuffers(1, &travelingBuffer);
}
void ProcessGraph::linkPrograms() {
	GLuint fragment = readShader(GL_FRAGMENT_SHADER, "FragmentShader.glsl");
	GLuint vertex = readShader(GL_VERTEX_SHADER, "VertexShader.glsl");
	GLuint opacity = readShader(GL_VERTEX_SHADER, "OpacityShader.glsl");

	program = makeProgram({fragment, vertex});
	opacityProgram = makeProgram({fragment, opacity});
}

void ProcessGraph::drawTravelings() {
	GLint projectionMatrix = glGetUniformLocation(program, "projectionMatrix");
	GLint drawingColor = glGetUniformLocation(program, "drawingColor");
	
	glBindBuffer(GL_ARRAY_BUFFER, travelingBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * (2 + 0), 0);

	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projection.data());
	glUniform3f(drawingColor, 0.f, 1.f, 0.f);

	glDrawArrays(GL_QUADS, 0, m_points.size() * 4);
}
float* ProcessGraph::generateTravelings() {
	float* res = new float[m_points.size() * 4 * (2 + 0)];
	size_t i = 0;

	for (TravelingPoint* n : m_points)
		generateQuad(res, i, n->p(), NODE_SIZE);
	return res;
}

void ProcessGraph::mouseReleaseEvent(QMouseEvent * ev) {
	drawTempLine = false;
	Point thisMousePos = translate(ev->pos());
	if (lastMousePos == thisMousePos) {
		if (ev->button() == Qt::MouseButton::LeftButton)
			leftMouseButtonClick(thisMousePos, ev);
		else if (ev->button() == Qt::MouseButton::RightButton)
			rightMouseButtonClick(thisMousePos, ev);
		else if (ev->button() == Qt::MouseButton::MiddleButton)
			middleMouseButtonClick(thisMousePos, ev);
	} else
		if (ev->button() == Qt::MouseButton::LeftButton)
			leftMouseButtonSwipe(thisMousePos, ev);
		else if (ev->button() == Qt::MouseButton::RightButton)
			rightMouseButtonSwipe(thisMousePos, ev);

	update();
}
void ProcessGraph::middleMouseButtonClick(Point mousePos, QMouseEvent * ev) {
	if (isNode(mousePos))
		m_points.insert(new TravelingPoint(this, findNode(mousePos)));
}