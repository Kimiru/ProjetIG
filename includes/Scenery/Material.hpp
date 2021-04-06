#pragma once

#include <GL/gl.h>

namespace Scenery {

	class Material {
		// GL_AMBIENT GL_DIFFUSE GL_SPECULAR GL_EMISSION GL_SHININESS
	public:
		bool doAmbiant = false, doDiffuse = false, doSpecular = false, doEmission = false, doShininess = false;
		float ambiant_values[4] = { 0,0,0,0 }, diffuse_values[4] = { 0,0,0,0 }, specular_values[4] = { 0,0,0,0 }, emission_values[4] = { 0,0,0,0 }, shininess_value = 0;
		int side = GL_FRONT;
		bool doCull = true;
		int cullingFace = GL_BACK;

		Material& ambiant(float r, float g, float b, float a);
		Material& diffuse(float r, float g, float b, float a);
		Material& specular(float r, float g, float b, float a);
		Material& emission(float r, float g, float b, float a);
		Material& shininess(float value);
		Material& front();
		Material& back();
		Material& frontAndBack();
		Material& cullFront();
		Material& cullBack();
		Material& cullNone();
		void use();

		static void save();
		static void base();
		static void restore();

	};

}