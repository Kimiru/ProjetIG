#pragma once

#include <Matrix/Vec.hpp>
#include <ostream>

namespace Matrix {

	template<int N>
	class Mat {

	public:

		float data[N][N];

		/**
		 * Create an empty matrix  
		 */
		Mat() {
			for (int line = 0; line < N; line++)
				for (int column = 0; column < N; column++)
					data[line][column] = 0;
		}

		/**
		 * Create a matrix and copy the value array
		 */
		Mat(float values[N][N]) {
			for (int line = 0; line < N; line++)
				for (int column = 0; column < N; column++)
					data[line][column] = values[line][column];
		}

		/**
		 * Convert a N size matrix to a M size matrix, add zeros if needed
		 */
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

		/**
		 * Return the column which index is index
		 */
		float* operator[](int index) {
			return data[index];
		}

		/**
		 * Reverse the matrix
		 */
		Mat<N> operator!() {
			float _det = det();
			if (_det == 0)
				return Mat<N>::id();
			_det = 1 / _det;
			return commatrix().transpose() * _det;
		}

		/**
		 * Multiply 2 matrix and return the result
		 */
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

		/**
		 * Multiply all member of the matrix by n and return the result
		 */
		Mat<N> operator*(float n) {
			Mat<N> res;
			for (int column = 0; column < N; column++)
				for (int line = 0; line < N; line++)
					res.data[column][line] = data[column][line] * n;
			return res;
		}

		/**
		 * Multiply a matrix with a vector and return the result
		 */
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
		 * Return the indentity matrix
		 */
		static Mat<N> id() {
			Mat<N> res;
			for (int index = 0; index < N; index++)
				res.data[index][index] = 1;
			return res;
		}

		/**
		 * Return the rotation matrix of a given angle on the x axis
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
		 * Return the rotation matrix of a given angle on the y axis
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
		 * Return the rotation matrix of a given angle on the z axis
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
		 * Return a rotation matrix along the axis x,y,z 
		 * x, y and z have to be normalized
		 */
		static Mat<N> rot(float angle, float x, float y, float z) {
			Mat<4> res = Mat<4>::id();

			float c = cos(angle);
			float s = sin(angle);

			res[0][0] = x * x + c * (1 - x * x);
			res[1][0] = x * y * (1 - c) - z * s;
			res[2][0] = x * z * (1 - c) + y * s;
			res[0][1] = x * y * (1 - c) + z * s;
			res[1][1] = y * y + c * (1 - y * y);
			res[2][1] = y * z * (1 - c) - x * s;
			res[0][2] = x * z * (1 - c) - y * s;
			res[1][2] = y * z * (1 - c) + x * s;
			res[2][2] = z * z + c * (1 - z * z);

			return res;

		}


		/**
		 * Return the translation matrix of given values
		 */
		static Mat<N> translate(float values[N - 1]) {
			Mat<N> res = Mat<4>::id();
			for (int line = 0; line < N - 1; line++)
				res.data[N - 1][line] = values[line];

			return res;
		}

		/**
		 * Return the translation matrix of given values
		 */
		static Mat<4> translate(float x, float y, float z) {
			Mat<N> res = Mat<4>::id();
			res.data[3][0] = x;
			res.data[3][1] = y;
			res.data[3][2] = z;
			return res;
		}

		/**
		 * Return a scale matrix
		 */
		static Mat<N> scale(float values[N - 1]) {
			Mat<N> res = Mat<N>::id();
			for (int i = 0; i < N - 1; i++)
				res.data[i][i] = values[i];
			return res;
		}

		/**
		 * Return a matrix with column and line inverted
		 */
		Mat<N> transpose() {
			Mat<N> res = Mat<N>::id();

			for (int column = 0; column < N; column++)
				for (int line = 0; line < N; line++)
					res.data[column][line] = data[line][column];

			return res;
		}

		/**
		 * Return the commatrix
		 */
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

		/**
		 * Return the determinant of the matrix
		 */
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

/**
 * Printing the matrix
 */
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

