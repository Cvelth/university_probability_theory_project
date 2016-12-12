#include <TravelingPoint.hpp>
#include <ProcessGraph.hpp>
#include <functional>

TravelingPoint::TravelingPoint(ProcessGraph* g, Node* n) : m_graph(g), m_v(1.f) {
	gen = new std::mt19937_64(std::random_device()());
	dist = new std::uniform_real_distribution<float>(0.f, 1.f);

	m_coords = n->p();

	m_thread = std::thread([&]() {
		while (true) {
			advance();
			std::this_thread::sleep_for(std::chrono::milliseconds(STEP_TIME));
		}
	});
}

TravelingPoint::~TravelingPoint() {
	m_thread.join();
	delete gen;
	delete dist;
}

void TravelingPoint::advance() {
	if (m_graph->isNode(m_coords))
		chooseNextPath(m_graph->findNode(m_coords));

	while (m_speed.length() < 0.07f)
		m_speed += m_speed;
	m_coords += m_speed;

	m_graph->update();
}

void TravelingPoint::chooseNextPath(Node* n) {
	float way = (*dist)(*gen);
	Link* link = nullptr;
	for (Link* l : *m_graph->links()) {
		if (*l->b() == *n) {
			link = l;
			way -= link->v();
		}
		if (way < 0.f)
			break;
	}

	if (link) {
		m_coords = n->p();

		Point linkVector = link->e()->p() - link->b()->p();
		m_speed = linkVector / STEPS_PER_LINK;
	} else {
		delete this;
	}
}
