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
	useTexture = false;
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

Scenery::Vertex::Vertex(std::initializer_list<float> list)
{
	useTexture = false;
	auto it = list.begin();
	position[0] = *it++;
	position[1] = *it++;
	position[2] = *it++;
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
