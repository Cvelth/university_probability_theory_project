#include <Graph.hpp>

bool Node::operator<(const Node& n) {
	return m_id < n.m_id;
}

bool Node::operator==(const Node & n) {
	return m_id == n.m_id;
}

size_t Node::ID = 0;
void Node::initializeNodding() {
	ID = 0;
}

Link::Link(Node* f, Node* s) {
	if (f == nullptr || f == nullptr)
		throw NullPointerException();
	m_f = f;
	m_s = s;
}

Node* Link::b() {
	return m_f;
}

Node* Link::e() {
	return m_s;
}

void Graph::add(Node* n) {
	m_nodes.insert(n);
}

void Graph::add(Link* l) {
	m_links.insert(l);
}

void Graph::remove(Node* n) {
	m_nodes.erase(n);
}

void Graph::remove(Link* l) {
	m_links.erase(l);
}

bool Graph::isNode(const Point & p) {
	for (Node* n : m_nodes)
		if (n->p() == p)
			return true;
	return false;
}

Node * Graph::findNode(const Point & p) {
	for (Node* n : m_nodes)
		if (n->p() == p)
			return n;
	return nullptr;
}
