#include <Scenery/Euler.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

Scenery::Euler::Euler()
{
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	order = Order::XYZ;
}

Scenery::Euler::Euler(float x, float y, float z, Order o)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	order = o;
}

float& Scenery::Euler::x()
{
	return data[0];
}

float& Scenery::Euler::x(float n)
{
	built = false;
	data[0] = n;
	return data[0];
}

float& Scenery::Euler::rx(float n)
{
	built = false;
	data[0] += n;
	return data[0];
}

float& Scenery::Euler::y()
{
	return data[1];
}

float& Scenery::Euler::y(float n)
{
	built = false;
	data[1] = n;
	return data[1];
}

float& Scenery::Euler::ry(float n)
{
	built = false;
	data[1] += n;
	return data[1];
}

float& Scenery::Euler::z()
{
	return data[2];
}

float& Scenery::Euler::z(float n)
{
	built = false;
	data[2] = n;
	return data[2];
}

float& Scenery::Euler::rz(float n)
{
	built = false;
	data[2] += n;
	return data[2];
}

void Scenery::Euler::build()
{
	rotationMatrix = Mat<4>::id();

	if (buildOrder == BuildOrder::GL) {
		for (int i = 0; i < 3; i++) {
			int cstep = step(i);
			if (data[cstep] != 0)
				rotationMatrix = rotationMatrix * getMatrixStep(i);
		}
	}
	else {
		for (int i = 2; i >= 0; i--) {
			int cstep = step(i);
			if (data[cstep] != 0)
				rotationMatrix = rotationMatrix * getMatrixStep(i);
		}
	}

	built = true;
}

Mat<4> Scenery::Euler::getMatrixStep(int wantedStep)
{
	int currentStep = step(wantedStep);
	if (currentStep == 0)
		return Mat<4>::rotX(data[0]);
	if (currentStep == 1)
		return Mat<4>::rotY(data[1]);
	else
		return Mat<4>::rotZ(data[2]);
}

Mat<4> Scenery::Euler::getMatrix()
{
	if (!built)
		build();
	return rotationMatrix;
}

void Scenery::Euler::applyGLRotate()
{
	if (built) {
		glMultMatrixf((float*)rotationMatrix.data);
	}
	else {

		for (int i = 0; i < 3; i++) {
			int currentStep = step(i);
			switch (currentStep)
			{
			case 0:
				if (data[0] == 0) continue;
				glRotatef(data[0] * 180.0f / (float)M_PI, 1.0f, 0.0f, 0.0f);
				break;
			case 1:
				if (data[1] == 0) continue;
				glRotatef(data[1] * 180.0f / (float)M_PI, 0.0f, 1.0f, 0.0f);
				break;
			case 2:
				if (data[2] == 0) continue;
				glRotatef(data[2] * 180.0f / (float)M_PI, 0.0f, 0.0f, 1.0f);
				break;
			}
		}
	}
}

bool Scenery::Euler::isRotation()
{
	return data[0] != 0 || data[1] != 0 || data[2] != 0;
}

int Scenery::Euler::step(int step)
{
	if (order == Order::XYZ)
		return step;
	else if (order == Order::XZY)
		return (3 - step) % 3;
	else if (order == Order::YXZ)
		return (4 - step) % 3;
	else if (order == Order::YZX)
		return (2 + step) % 3;
	else if (order == Order::ZXY)
		return (step + 1) % 3;
	else
		return 2 - step;
}

std::ostream& operator<<(std::ostream& os, const Scenery::Euler& v) {
	os << "Euler(" << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << ")" << std::endl;
	return os;
}