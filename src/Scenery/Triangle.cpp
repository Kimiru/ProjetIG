#include <Scenery/Triangle.hpp>
#include <Scenery/Vertex.hpp>


Scenery::Triangle::Triangle()
{
	_1 = _2 = _3 = NULL;
}

Scenery::Triangle::Triangle(Vertex* _1, Vertex* _2, Vertex* _3) : _1(_1), _2(_2), _3(_3) {}

void Scenery::Triangle::renormalize()
{
	Vec<4> normal = Vertex::getNormal(*_1, *_2, *_3);
	_1->normal = _2->normal = _3->normal = normal;
	
}

void Scenery::Triangle::start()
{
	glBegin(GL_TRIANGLES);
}

void Scenery::Triangle::end()
{
	glEnd();
}

void Scenery::Triangle::draw()
{
	_1->use();
	_2->use();
	_3->use();
}
