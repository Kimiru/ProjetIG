#include <Scenery/Vertex.hpp>

Vec<3> Scenery::Vertex::operator>>(Vertex v)
{
	return v.position - position;
}

Scenery::Vertex::Vertex()
{
	useTexture = false;
}

Scenery::Vertex::Vertex(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Scenery::Vertex::setTexPos(float x, float y)
{
	useTexture = true;
	texturePosition[0] = x;
	texturePosition[1] = y;
}

void Scenery::Vertex::use()
{
	glNormal3fv(normal.data);
	glVertex3fv(position.data);
	if (useTexture)
		glTexCoord2fv(texturePosition.data);
}

Vec<3> Scenery::Vertex::getNormal(Vertex v1, Vertex v2, Vertex v3)
{
	return (v1 >> v2) ^ (v1 >> v3);
}
