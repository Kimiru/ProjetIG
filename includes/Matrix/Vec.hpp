#pragma once

#include <iostream>
#include <stdarg.h>

namespace Matrix {

	template<int N>
	class Vec {

	public:

		float data[N];

		/**
		 * Create an empty vector 
		 */
		Vec() {
			for (int i = 0; i < N; i++)
				data[i] = 0;
		}

		/**
		 * Create a vector from values array
		 */
		Vec(float values[N]) {
			for (int i = 0; i < N; i++) {
				data[i] = values[i];
			}
		}

		/**
		 * Create a vector from initializer list
		 * If missing values, replaced by 0
		 */
		Vec(std::initializer_list<float> list) {
			auto it = list.begin();
			int index = 0;
			while (it != list.end() && index < N) {
				data[index] = *it;
				it++;
				index++;
			}
			while (index < N) {
				data[index++] = 0;
			}
		}

		/**
		 * Convert a N size vector to a M size vector 
		 */
		template<int M>
		operator Vec<M>() {
			Vec<M> res;
			if (M < N) {
				for (int i = 0; i < M; i++)
					res[i] = this->data[i];
			}
			else {
				for (int i = 0; i < M; i++)
					if (i < N)
						res[i] = data[i];
					else
						res[i] = 0;
			}
			return res;
		}

		/**
		 * Return the value at the given index
		 */
		float& operator[](int index) {
			return data[index];
		}

		/**
		 * Return the vector product
		 */
		Vec<3> operator^(const Vec<3> v) {
			Vec<3> res;
			res.data[0] = data[1] * v.data[2] - data[2] * v.data[1];
			res.data[1] = data[2] * v.data[0] - data[0] * v.data[2];
			res.data[2] = data[0] * v.data[1] - data[1] * v.data[0];
			return res;
		}

		/**
		 * Return the scalar product
		 */
		float operator*(const Vec<N> v) {
			float res = 0;
			for (int i = 0; i < N; i++)
				res += data[i] * v.data[i];
			return res;
		}

		/**
		 * Return the sum of vectors
		 */
		Vec<N> operator+(const Vec<N> v) {
			Vec<N> res;
			for (int i = 0; i < N; i++)
				res.data[i] = data[i] + v.data[i];
			return res;
		}

		/**
		 * Add the given vector to the vector
		 */
		void operator+=(const Vec<N> v) {
			for (int i = 0; i < N; i++)
				data[i] += v.data[i];
		}

		/**
		 * Return the substraction of vectors
		 */
		Vec<N> operator-(const Vec<N> v) {
			Vec<N> res;
			for (int i = 0; i < N; i++)
				res.data[i] = data[i] - v.data[i];
			return res;
		}

		/**
		 * Substract the given vector to the vector
		 */
		void operator-=(const Vec<N> v) {
			for (int i = 0; i < N; i++)
				data[i] -= v.data[i];
		}

		/**
		 * Multiply each value of the vector by n
		 * Returns the result
		 */
		Vec<N> operator*(float n) {
			Vec<N> res;
			for (int i = 0; i < N; i++)
				res.data[i] = data[i] * n;
			return res;
		}

		/**
		 * Multiply each value by n
		 * Return itself
		 */
		Vec<N> operator*=(float n) {
			for (int i = 0; i < N; i++)
				data[i] *= n;
			return *this;
		}

		/**
		 * Divide each value of the vector by n
		 * Returns the result
		 */
		Vec<N> operator/(float n) {
			Vec<N> res;
			for (int i = 0; i < N; i++)
				res.data[i] = data[i] / n;
			return res;
		}

		/**
		 * Divide each value of the vector by n
		 * Returns itself
		 */
		Vec<N> operator/=(float n) {
			for (int i = 0; i < N; i++)
				data[i] /= n;
			return *this;
		}

		/**
		 * Define the last value by n
		 * Returns itself
		 */
		Vec<N> operator<<(float n) {
			data[N - 1] = n;
			return *this;
		}


		/**
		 *	Return the vector with the minimum value of both vector
		 */
		Vec<N> operator<(Vec<N> v) {
			Vec<N> res;
			for (int i = 0; i < N; i++) {
				res.data[i] = v.data[i] > data[i] ? data[i] : v.data[i];
			}
			return res;
		}

		/**
		 *	Return the vector with the maximum value of both vector
		 */
		Vec<N> operator>(Vec<N> v) {
			Vec<N> res;
			for (int i = 0; i < N; i++) {
				res.data[i] = v.data[i] < data[i] ? data[i] : v.data[i];
			}
			return res;
		}


		/**
		 *	Return the vector with opposite value of each data.
		 */
		Vec<N> operator-() {
			Vec<N> res;
			for (int i = 0; i < N; i++) {
				res.data[i] = -data[i];
			}
			return res;
		}

		/**
		 * Return the vector with each value positive
		 **/
		Vec<N> abs() {
			Vec<N> res;
			for (int i = 0; i < N; i++) {
				res.data[i] = data[i] >= 0 ? data[i] : -data[i];
			}
			return res;
		}

		/**
		 * Return the vector representing the sign of each value
		 */
		Vec<N> sign() {
			Vec<N> res;
			for (int i = 0; i < N; i++) {
				res.data[i] = data[i] >= 0 ? 1 : -1;
			}
			return res;
		}


		/**
		 *	Multiply 2 vectors, value by value
		 */
		Vec<N> multiply(Vec<N> v) {
			Vec<N> res;
			for (int i = 0; i < N; i++) {
				res.data[i] = data[i] * v.data[i];
			}
			return res;
		}

		/**
		 * Define the content of the vector with a given list
		 */
		void set(std::initializer_list<float> list) {
			int index = 0;
			auto it = list.begin();
			while (it != list.end() && index < N) {
				data[index++] = *it++;
			}
		}

		/**
		 * Return the angle of the vector in a given plan
		 */
		float angle(int x, int y) {
			Vec<2> v = Vec<2>({ data[x], data[y] });
			v.normalize();
			float _acos = acos(v.data[0]);
			float _asin = asin(v.data[1]);
			float sign = _asin >= 0 ? 1 : -1;
			return _acos * sign;
		}

		/**
		 * Return the length of a vector
		 */
		float length() {
			float res = 0;
			for (int i = 0; i < N; i++) res += data[i] * data[i];
			res = sqrt(res);
			return res;
		}

		/**
		 * Normalize the vector
		 */
		void normalize() {
			float length = this->length();
			*this /= length;
		}

		/**
		 * Check if all values are equal to a given value
		 */
		bool all(float value) {
			for (int i = 0; i < N; i++)
				if (data[i] != value) return false;
			return true;
		}

	};

};

/**
 * Print the vector
 */
template<int N>
std::ostream& operator<<(std::ostream& os, const Matrix::Vec<N>& v) {
	os << "Vector<" << N << ">(";
	for (int i = 0; i < N; i++) {
		if (i != 0)
			os << ", ";
		os << v.data[i];
	}
	os << ")" << std::endl;
	return os;
}