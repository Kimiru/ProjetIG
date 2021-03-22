#pragma once

#include <vector>

#include <GL/gl.h>

namespace Scenery {

	class Light {

	private:

		static std::vector<int> availableLights;
		bool enabled = false;
		int myLight = -1;

		bool doAmbiant = false, doDiffuse = false, doSpecular = false, hasPosition = false, doSpotDirection = false;
		float ambiant_values[4] = { 0,0,0,0 }, diffuse_values[4] = { 0,0,0,0 }, specular_values[4] = { 0,0,0,0 }, position_values[4] = { 0,0,0,0 }, spotDirection_values[3] = { 0,0,0 };
		float spotExponentValue = -1, spotCutoffValue = -1;
		float constantAttenuationValue = -1, linearAttenuationValue = -1, quadraticAttenuationValue = -1;

	public:

		~Light();

		Light& position(float x, float y, float z);
		Light& direction(float x, float y, float z);
		Light& ambiant(float r, float g, float b, float a);
		Light& diffuse(float r, float g, float b, float a);
		Light& specular(float r, float g, float b, float a);
		Light& spotDirection(float x, float y, float z);
		Light& spotExponent(float value);
		Light& spotCutoff(float angle);
		Light& constantAttenuation(float value);
		Light& linearAttenuation(float value);
		Light& quadraticAttenuation(float value);

		void turn(bool enabled);
		void turnOn();
		void turnOff();
		void use();

	};

}