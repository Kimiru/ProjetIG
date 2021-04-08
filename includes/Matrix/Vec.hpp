#pragma once

#include <iostream>
#include <stdarg.h>

namespace Matrix {

	template<int N>
	class Vec {

	public:

		float data[N];

		/// <summary>
		/// Create a Vector of size N.
		/// 
		/// Create a Vector of size N where all the values are initialized 
		/// with the value 0.
		/// </summary>
		Vec() {
			for (int i = 0; i < N; i++)
				data[i] = 0;
		}

		/// <summary>
		/// Create a Vector of size N.
		/// 
		/// Create a Vector of size N where the values are define by array
		/// of size N given as parameter.
		/// </summary>
		/// <param name="values">The array of values used to set the Vector default values.</param>
		Vec(float values[N]) {
			for (int i = 0; i < N; i++) {
				data[i] = values[i];
			}
		}

		Vec(std::initializer_list<float> list) {
			auto it = list.begin();
			int index = 0;
			while (it != list.end() && index < N) {
				data[index] = *it;
				it++;
				index++;
			}
		}

		/// <summary>
		/// Convert a Vector.
		/// 
		/// Convert a Vector of size N to a Vector of Size M. Adding zeros
		/// or removing values if necessary.
		/// </summary>
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

		/// <summary>
		/// Get a value of the Vector.
		/// 
		/// Get an editable value of the Vector from a given index.
		/// </summary>
		/// <param name="index">The index to get the value from.</param>
		/// <returns>A reference to the value at the given index.</returns>
		float& operator[](int index) {
			return data[index];
		}

		/// <summary>
		/// Calculate Vector product.
		/// 
		/// Calculate the Vector product between this Vector and a given Vector.
		/// </summary>
		/// <param name="v">The Vector which to do the product with.</param>
		/// <returns>A new Vector, result of the product between this and the Vector v.</returns>
		Vec<3> operator^(const Vec<3> v) {
			Vec<3> res;
			res.data[0] = data[1] * v.data[2] - data[2] * v.data[1];
			res.data[1] = data[2] * v.data[0] - data[0] * v.data[2];
			res.data[2] = data[0] * v.data[1] - data[1] * v.data[0];
			return res;
		}

		float operator*(const Vec<N> v) {
			float res = 0;
			for (int i = 0; i < N; i++)
				res += data[i] * v.data[i];
			return res;
		}

		Vec<N> operator+(const Vec<N> v) {
			Vec<N> res;
			for (int i = 0; i < N; i++)
				res.data[i] = data[i] + v.data[i];
			return res;
		}

		void operator+=(const Vec<N> v) {
			for (int i = 0; i < N; i++)
				data[i] += v.data[i];
		}

		Vec<N> operator-(const Vec<N> v) {
			Vec<N> res;
			for (int i = 0; i < N; i++)
				res.data[i] = data[i] - v.data[i];
			return res;
		}

		void operator-=(const Vec<N> v) {
			for (int i = 0; i < N; i++)
				data[i] -= v.data[i];
		}

		Vec<N> operator*(float n) {
			Vec<N> res;
			for (int i = 0; i < N; i++)
				res.data[i] = data[i] * n;
			return res;
		}

		Vec<N> operator*=(float n) {
			for (int i = 0; i < N; i++)
				data[i] *= n;
			return *this;
		}

		Vec<N> operator/(float n) {
			Vec<N> res;
			for (int i = 0; i < N; i++)
				res.data[i] = data[i] / n;
			return res;
		}

		Vec<N> operator/=(float n) {
			for (int i = 0; i < N; i++)
				data[i] /= n;
			return *this;
		}

		/// <summary>
		/// Set value at then end
		/// 
		/// Set a given value at end of the vector.
		/// 
		/// Can be used to set last value while operating with
		/// homogeneous coordinates.
		/// </summary>
		/// <param name="n">The value to set at then end of the vector.</param>
		/// <returns>A reference to this.</returns>
		Vec<N> operator<<(float n) {
			data[N - 1] = n;
			return *this;
		}

		void set(std::initializer_list<float> list) {
			int index = 0;
			auto it = list.begin();
			while (it != list.end() && index < N) {
				data[index++] = *it++;
			}
		}

		float angle(int x, int y) {
			Vec<2> v = Vec<2>({ data[x], data[y] });
			v.normalize();
			float _acos = acos(v.data[0]);
			float _asin = asin(v.data[1]);
			float sign = _asin >= 0 ? 1 : -1;
			return _acos * sign;
		}

		float length() {
			float res = 0;
			for (int i = 0; i < N; i++) res += data[i] * data[i];
			res = sqrt(res);
			return res;
		}

		void normalize() {
			float length = this->length();
			*this /= length;
		}

		bool all(float value) {
			for (int i = 0; i < N; i++)
				if (data[i] != value) return false;
			return true;
		}

	};

};


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