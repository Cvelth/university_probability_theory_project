#pragma once
#include <Point.hpp>
#include <set>

class NullPointerException {};

class Node {
private:
	size_t m_id;
	Point m_c;

	static size_t ID;
public:
	explicit Node(Point p = Point()) : Node(p, ID++) {};

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

	bool operator<(const Node& n);
	bool operator==(const Node& n);

	static void initializeNodding();
protected:
	Node(Point p, size_t id) : m_c(p), m_id(id) {};
};

class Link {
private:
	Node* m_f;
	Node* m_s;
public:
	explicit Link(Node* f, Node* s);
	Node* b();
	Node* e();
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
};