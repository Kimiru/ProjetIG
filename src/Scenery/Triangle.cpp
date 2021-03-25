#include <Scenery/Triangle.hpp>
#include <Scenery/Vertex.hpp>


Scenery::Triangle::Triangle(Vertex& _1, Vertex& _2, Vertex& _3) :_1(_1), _2(_2), _3(_3) {}

void Scenery::Triangle::draw()
{
	glBegin(GL_TRIANGLES);
	_1.use();
	_2.use();
	_3.use();
	glEnd();

}
