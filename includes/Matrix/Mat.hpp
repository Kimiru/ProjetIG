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
			return res;
		}

		float* operator[](int index) {
			return data[index];
		}
		Mat<N> operator!() {
			float _det = det();
			if (_det == 0)
				return Mat<N>::id();
			_det = 1 / _det;
			return commatrix().transpose() * _det;
		}

		Mat<N> operator*(Mat<N> m) {
			Mat<N> res;
			for (int column = 0; column < N; column++)
				for (int line = 0; line < N; line++) {
					res.data[column][line] = 0;
					for (int depth = 0; depth < N; depth++)
						res.data[column][line] += data[column][depth] * m.data[depth][line];
				}
			return res;
		}
		Mat<N> operator*(float n) {
			Mat<N> res;
			for (int column = 0; column < N; column++)
				for (int line = 0; line < N; line++)
					res.data[column][line] = data[column][line] * n;
			return res;
		}
		Vec<N> operator*(Vec<N> v) {
			Vec<N> res;
			for (int line = 0; line < N; line++) {
				res[line] = 0;
				for (int depth = 0; depth < N; depth++) {
					res.data[line] += data[depth][line] * v.data[depth];
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
			for (int line = 0; line < N - 1; line++)
				res.data[N - 1][line] = values[line];

			return res;
		}

		static Mat<4> translate(float x, float y, float z) {
			Mat<N> res = Mat<4>::id();
			res.data[3][0] = x;
			res.data[3][1] = y;
			res.data[3][2] = z;
			return res;
		}

		static Mat<N> scale(float values[N - 1]) {
			Mat<N> res = Mat<N>::id();
			for (int i = 0; i < N - 1; i++)
				res.data[i][i] = values[i];
			return res;
		}

		Mat<N> transpose() {
			Mat<N> res = Mat<N>::id();

			for (int column = 0; column < N; column++)
				for (int line = 0; line < N; line++)
					res.data[column][line] = data[line][column];

			return res;
		}

		Mat<N> commatrix() {
			Mat<N> res = Mat<N>::id();
			if  constexpr (N > 1) {
				Mat<N - 1> mat;

				for (int column = 0; column < N; column++) {
					for (int line = 0; line < N; line++) {
						for (int col = 0; col < N; col++) {
							if (col == column) continue;
							int fixc = col > column ? -1 : 0;
							for (int li = 0; li < N; li++) {
								if (li == line) continue;
								int fixl = li > line ? -1 : 0;
								mat.data[col + fixc][li + fixl] = data[col][li];
							}
						}
						res.data[column][line] = mat.det() * ((column + line) % 2 == 0 ? 1 : -1);
					}
				}
			}
			return res;
		}

		float det() {
			if constexpr (N == 1)
				return data[0][0];
			else if constexpr (N == 2) {
				return (data[0][0] * data[1][1]) - (data[0][1] * data[1][0]);
			}
			else if  constexpr (N > 2) {
				int constexpr LINE = N - 1;
				float det = 0;

				Mat<LINE> mat;

				for (int column = 0; column < N; column++) {
					for (int col = 0; col < N; col++) {
						if (col == column) continue;
						int fix = col > column ? -1 : 0;
						for (int line = 0; line < LINE; line++) {
							mat.data[col + fix][line] = data[col][line];
						}
					}
					det += data[column][LINE] * mat.det() * (column % 2 == 0 ? 1 : -1);
				}
				return det * (N % 2 == 0 ? -1 : 1);
			}
			return 0;
		}

	};

}

template<int N>
std::ostream& operator<<(std::ostream& os, const Matrix::Mat<N>& m) {
	os << "Matrix<" << N << ">" << std::endl;
	for (int column = 0; column < N; column++) {
		os << "[";
		for (int line = 0; line < N; line++) {
			if (line != 0)
				os << ", ";
			os << m.data[line][column];
		}
		os << "]" << std::endl;
	}
	return os;
}

