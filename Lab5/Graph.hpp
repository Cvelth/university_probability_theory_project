#pragma once
#include <Point.hpp>
#include <set>

class NullPointerException {};

class Node {
private:
	size_t m_id;
	Point m_c;

	float m_q;

	static size_t ID;
public:
	explicit Node(Point p = Point(), float q = 0.f) : Node(p, q, ID++) {};

	size_t id() {
		return m_id;
	}
	float x() {
		return m_c.x();
	}
	float y() {
		return m_c.y();
	}
	Point p() {
		return m_c;
	}
	float q() {
		return m_q;
	}
	void q(float _q) {
		m_q += _q;
	}

	bool operator<(const Node& n);
	bool operator==(const Node& n);

	static void initializeNodding();
protected:
	Node(Point p, float q, size_t id) : m_c(p), m_q(q), m_id(id) {};
};

class Link {
private:
	Node* m_f;
	Node* m_s;
	float m_v;
	float m_q;

public:
	explicit Link(Node* f, Node* s);
	explicit Link(Node* f, Node* s, float _v);
	~Link() {}
	Node* b();
	Node* e();
	float v();
	float q();

	void q(float _q);
	void v(float _v);
};

class Graph {
protected:
	std::set<Node*> m_nodes;
	std::set<Link*> m_links;

public:
	void add(Node* n);
	void add(Link* l);
	void remove(Node* n);
	void remove(Link* l);
	
	bool isNode(const Point& p);
	Node* findNode(const Point& p);
	Link* findLink(const Point& b, const Point& e);

	std::set<Link*>* links() { return &m_links; }
	std::set<Node*>* nodes() { return &m_nodes; }

protected:
	void changeWeights(Link* l, float q);
};