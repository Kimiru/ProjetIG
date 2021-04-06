#include <Scenery/Light.hpp>
#include <iostream>

std::vector<int> Scenery::Light::availableLights{ GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3 , GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };

Scenery::Light::~Light()
{
	turnOff();
}

Scenery::Light& Scenery::Light::position(float x, float y, float z)
{
	hasPosition = true;
	position_values[0] = x;
	position_values[1] = y;
	position_values[2] = z;
	position_values[3] = 1.0f;

	return *this;
}

Scenery::Light& Scenery::Light::direction(float x, float y, float z)
{
	hasPosition = true;
	position_values[0] = x;
	position_values[1] = y;
	position_values[2] = z;
	position_values[3] = 0.0f;
	return *this;
}

Scenery::Light& Scenery::Light::ambiant(float r, float g, float b, float a)
{
	doAmbiant = true;
	ambiant_values[0] = r;
	ambiant_values[1] = g;
	ambiant_values[2] = b;
	ambiant_values[3] = a;
	return *this;
}

Scenery::Light& Scenery::Light::diffuse(float r, float g, float b, float a)
{
	doDiffuse = true;
	diffuse_values[0] = r;
	diffuse_values[1] = g;
	diffuse_values[2] = b;
	diffuse_values[3] = a;
	return *this;
}

Scenery::Light& Scenery::Light::specular(float r, float g, float b, float a)
{
	doSpecular = true;
	specular_values[0] = r;
	specular_values[1] = g;
	specular_values[2] = b;
	specular_values[3] = a;
	return *this;
}

Scenery::Light& Scenery::Light::spotDirection(float x, float y, float z)
{
	doSpotDirection = true;
	spotDirection_values[0] = x;
	spotDirection_values[1] = y;
	spotDirection_values[2] = z;
	return *this;
}

Scenery::Light& Scenery::Light::spotExponent(float value)
{
	spotExponentValue = value;
	return *this;
}

Scenery::Light& Scenery::Light::spotCutoff(float angle)
{
	spotCutoffValue = angle;
	return *this;
}

Scenery::Light& Scenery::Light::constantAttenuation(float value)
{
	constantAttenuationValue = value;
	return *this;
}

Scenery::Light& Scenery::Light::linearAttenuation(float value)
{
	constantAttenuationValue = value;
	return *this;
}

Scenery::Light& Scenery::Light::quadraticAttenuation(float value)
{
	quadraticAttenuationValue = value;
	return *this;
}

void Scenery::Light::turn(bool enabled)
{
	if (this->enabled && !enabled) {
		glDisable(myLight);
		availableLights.push_back(myLight);
		myLight = -1;
		this->enabled = enabled;
	}
	if (!this->enabled && enabled) {
		myLight = availableLights[availableLights.size() - 1];
		availableLights.pop_back();
		glEnable(myLight);
		this->enabled = enabled;
	}
}

void Scenery::Light::turnOn()
{
	turn(true);
}

void Scenery::Light::turnOff()
{
	turn(false);
}

void Scenery::Light::use()
{
	if (!enabled)return;
	if (doAmbiant)
		glLightfv(myLight, GL_AMBIENT, ambiant_values);
	if (doDiffuse)
		glLightfv(myLight, GL_DIFFUSE, diffuse_values);
	if (doSpecular)
		glLightfv(myLight, GL_SPECULAR, specular_values);
	if (hasPosition)
		glLightfv(myLight, GL_POSITION, position_values);
	if (doSpotDirection)
		glLightfv(myLight, GL_SPOT_DIRECTION, spotDirection_values);
	if (spotExponentValue != -1)
		glLightf(myLight, GL_SPOT_EXPONENT, spotExponentValue);
	if (spotCutoffValue != -1)
		glLightf(myLight, GL_SPOT_CUTOFF, spotCutoffValue);
	if (constantAttenuationValue != -1)
		glLightf(myLight, GL_CONSTANT_ATTENUATION, constantAttenuationValue);
	if (linearAttenuationValue != -1)
		glLightf(myLight, GL_LINEAR_ATTENUATION, linearAttenuationValue);
	if (quadraticAttenuationValue != -1)
		glLightf(myLight, GL_QUADRATIC_ATTENUATION, quadraticAttenuationValue);

}
