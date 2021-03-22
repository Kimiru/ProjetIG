#pragma once

#include <Matrix/Vec.hpp>
#include <ostream>

namespace Matrix {

	template<int N>
	class Mat {

	public:

		float data[N][N];

		Mat() {
			for (int line = 0; line < N; line++)
				for (int column = 0; column < N; column++)
					data[line][column] = 0;
		}
		Mat(float values[N][N]) {
			for (int line = 0; line < N; line++)
				for (int column = 0; column < N; column++)
					data[line][column] = values[line][column];
		}

		template<int M>
		operator Mat<M>() {
			Mat<M> res;
			if (M < N) {
				for (int line = 0; line < M; line++)
					for (int column = 0; column < M; column++)
						res.data[line][column] = data[line][column];
			}
			else {
				for (int line = 0; line < M; line++)
					for (int column = 0; column < M; column++) {
						if (line < N && column < N)
							res.data[line][column] = data[line][column];
						else
							res.data[line][column] = 0;
					}
			}
			return res;
		}

		float* operator[](int index) {
			return data[index];
		}
		Mat<N> operator*(Mat<N> m) {
			Mat<N> res;
			for (int line = 0; line < N; line++)
				for (int column = 0; column < N; column++) {
					res[line][column] = 0;
					for (int depth = 0; depth < N; depth++)
						res[line][column] += data[line][depth] * m[depth][column];
				}
			return res;
		}
		Vec<N> operator*(Vec<N> v) {
			Vec<N> res;
			for (int line = 0; line < N; line++) {
				res[line] = 0;
				for (int depth = 0; depth < N; depth++) {
					res[line] = data[line][depth] * v[depth];
				}

			}
			return res;
		};

		/**
			Return the identity matrix
				 0    1    ...  N-1
				-----------------
			0	|1    0    0    0
			1   |0    1    0    0
			... |0    0    1    0
			N-1	|0    0    0    1

			@return Matrix4 the identity matrix
		 */
		static Mat<N> id() {
			Mat<N> res;
			for (int index = 0; index < N; index++)
				res.data[index][index] = 1;
			return res;
		}

		/**
			Return the rotation matrix of a given angle on the x axis
				1     0      0       0
				0     cos(a) -sin(a) 0
				0     sin(a) cos(a)  0
				0     0      0       1
			@return Matrix4 the rotation matrix
		 */
		static Mat<4> rotX(float angle) {
			Mat<4> res = Mat<4>::id();
			res[1][1] = cos(angle);
			res[2][1] = -sin(angle);
			res[1][2] = sin(angle);
			res[2][2] = cos(angle);
			return res;
		}

		/**
			Return the rotation matrix of a given angle on the y axis
				cos(a)  0       sin(a) 0
				0       1       0      0
				-sin(a) 0       cos(a) 0
				0       0       0      1
			@return Matrix4 the rotation matrix
		 */
		static Mat<4> rotY(float angle) {
			Mat<4> res = Mat<4>::id();
			res[0][0] = cos(angle);
			res[2][0] = -sin(angle);
			res[0][2] = sin(angle);
			res[2][2] = cos(angle);
			return res;
		}

		/**
			Return the rotation matrix of a given angle on the z axis
				cos(a)  -sin(a) 0      0
				sin(a)  cos(a)  0      0
				0       0       0      0
				0       0       0      1
			@return Matrix4 the rotation matrix
		 */
		static Mat<4> rotZ(float angle) {
			Mat<4> res = Mat<4>::id();
			res[0][0] = cos(angle);
			res[1][0] = -sin(angle);
			res[0][1] = sin(angle);
			res[1][1] = cos(angle);
			return res;
		}

		/**
			Return the translation matrix of given values
				1  0  0  x
				0  1  0  y
				0  0  1  z
				0  0  0  1
			@return Matrix4 the rotation matrix
		 */
		static Mat<N> translate(float values[N - 1]) {
			Mat<N> res = Mat<4>::id();
			for (int line = 0; line < N - 1; line++) {
				res.data[N - 1][line] = values[line];
			}
			return res;
		}

		static Mat<N> scale(float values[N - 1]) {
			Mat<N> res = Mat<N>::id();
			for (int i = 0; i < N - 1; i++)
				res[i][i] = values[i];
			return res;
		}
	};

}

template<int N>
std::ostream& operator<<(std::ostream& os, const Matrix::Mat<N>& m) {
	os << "Matrix<" << N << ">" << std::endl;
	for (int line = 0; line < N; line++) {
		os << "[";
		for (int column = 0; column < N; column++) {
			if (column != 0)
				os << ", ";
			os << m.data[line][column];
		}
		os << "]" << std::endl;
	}
	return os;
}