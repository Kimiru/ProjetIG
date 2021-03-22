#pragma once

#include <Matrix/Mat.hpp>

#include <GL/gl.h>

#include <ostream>

using namespace Matrix;
namespace Scenery {

	enum class Order
	{
		XYZ, XZY, YXZ, YZX, ZXY, ZYX
	};

	class Euler {
	public:

		float data[3];
		Order order;

		bool built = false;
		Mat<4> rotationMatrix;


		Euler();
		Euler(float x, float y, float z, Order o);

		float& x();
		float& x(float n);
		float& rx(float n);
		float& y();
		float& y(float n);
		float& ry(float n);
		float& z();
		float& z(float n);
		float& rz(float n);

		void build();
		Mat<4> getMatrixStep(int wantedStep);
		Mat<4> getMatrix();
		void applyGLRotate();
		bool isRotation();
		int step(int step);
	};

}

std::ostream& operator<<(std::ostream& os, const Scenery::Euler& v);