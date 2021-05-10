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
		float base[3] = { 0, 0, 0 };
		Order order;

		bool built = false;
		Mat<4> rotationMatrix;

		/**
		 * Create an Euler angle.
		 */
		Euler();
		Euler(float x, float y, float z, Order o);

		/**
		 * Return x
		 */
		float& x();

		/**
		 * Define and return x
		 */
		float& x(float n);

		/**
		 * Rotate and return x of n amount
		 */
		float& rx(float n);

		// Same for y and z
		float& y();
		float& y(float n);
		float& ry(float n);
		float& z();
		float& z(float n);
		float& rz(float n);


		/**
		 * Define a default angle
		 */
		void setBase(std::initializer_list<float> list);

		/**
		 * Get back to a default angle
		 */
		void reset();

		/**
		 * Precompute the transformation matrix
		 */
		void build();

		/**
		 * Return the given step of the transformation matrix
		 */
		Mat<4> getMatrixStep(int wantedStep);

		/**
		 * Return the transformation matrix and compute it if needed
		 */
		Mat<4> getMatrix();

		/**
		 * Apply GLRotate according to the angle
		 */
		void applyGLRotate();

		/**
		 * Check if there is none value equals to 0
		 */
		bool isRotation();

		/**
		 * Return the given step
		 */
		int step(int step);
	};

}

std::ostream& operator<<(std::ostream& os, const Scenery::Euler& v);