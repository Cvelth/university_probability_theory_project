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

Link::Link(Node* f, Node* s) : Link(f, s, 1.f) {};

Link::Link(Node* f, Node* s, float _v) {
	if (f == nullptr || f == nullptr)
		throw NullPointerException();
	m_f = f;
	m_s = s;

	v(_v);
}

Node* Link::b() {
	return m_f;
}

Node* Link::e() {
	return m_s;
}

float Link::v() {
	return m_v;
}

void Link::v(float v) {
	if (v > 1.f)
		m_v = 1.f;
	else if (v < 0.f)
		m_v = 0.f;
	else
		m_v = v;
}

void Graph::add(Node* n) {
	m_nodes.insert(n);
}

void Graph::add(Link* l) {
	m_links.insert(l);
}

void Graph::remove(Node* n) {
	for (auto i = m_links.begin(); i != m_links.end(); i++)
		if (*n == *(*i)->b(), *n == *(*i)->e())
			i = m_links.erase(i);
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

Node* Graph::findNode(const Point & p) {
	for (Node* n : m_nodes)
		if (n->p() == p)
			return n;
	return nullptr;
}

Link* Graph::findLink(const Point & b, const Point & e) {
	Node* bn = findNode(b);
	Node* en = findNode(e);
	for (Link* l : m_links)
		if (*bn == *l->b() && *en == *l->e())
			return l;
	return nullptr;
}
