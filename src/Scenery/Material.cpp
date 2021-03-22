#include <Scenery/Material.hpp>
#include <iostream>

Scenery::Material& Scenery::Material::ambiant(float r, float g, float b, float a)
{
	doAmbiant = true;
	ambiant_values[0] = r;
	ambiant_values[1] = g;
	ambiant_values[2] = b;
	ambiant_values[3] = a;

	return *this;
}

Scenery::Material& Scenery::Material::diffuse(float r, float g, float b, float a)
{
	doDiffuse = true;
	diffuse_values[0] = r;
	diffuse_values[1] = g;
	diffuse_values[2] = b;
	diffuse_values[3] = a;

	return *this;
}

Scenery::Material& Scenery::Material::specular(float r, float g, float b, float a)
{
	doSpecular = true;
	specular_values[0] = r;
	specular_values[1] = g;
	specular_values[2] = b;
	specular_values[3] = a;

	return *this;
}

Scenery::Material& Scenery::Material::emission(float r, float g, float b, float a)
{
	doEmission = true;
	emission_values[0] = r;
	emission_values[1] = g;
	emission_values[2] = b;
	emission_values[3] = a;

	return *this;
}

Scenery::Material& Scenery::Material::shininess(float value)
{
	doShininess = true;
	shininess_value = value;

	return *this;
}

Scenery::Material& Scenery::Material::front()
{
	side = GL_FRONT;

	return *this;
}

Scenery::Material& Scenery::Material::back()
{
	side = GL_BACK;
	return *this;
}

Scenery::Material& Scenery::Material::frontAndBack()
{
	side = GL_FRONT_AND_BACK;
	return *this;
}

void Scenery::Material::use()
{
	if (doAmbiant)
		glMaterialfv(side, GL_AMBIENT, ambiant_values);
	if (doDiffuse)
		glMaterialfv(side, GL_DIFFUSE, diffuse_values);
	if (doSpecular)
		glMaterialfv(side, GL_SPECULAR, specular_values);
	if (doEmission)
		glMaterialfv(side, GL_EMISSION, emission_values);
	if (doShininess)
		glMaterialf(side, GL_SHININESS, shininess_value);

	int err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "Error using material " << err << std::endl;
}
