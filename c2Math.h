#ifndef CHIS2D_MATH
#define CHIS2D_MATH
#include <cmath>
#define MAXN 1000
#define offset 10000
#define eps 1e-8
#define PI 3.14159265358979323846//acos(-1.0)
//判断一个数是否为0,是则返回true,否则返回false
#define zero(x)(((x)>0?(x):-(x))<eps)
//返回一个数的符号，正数返回1，负数返回2，否则返回0
#define _sign(x)((x)>eps?1:((x)<-eps?2:0))

namespace chis {
	/// 
	using real = double;
	/**
	* Holds a vector in 2 dimensions.
	**/ 
	class Vector2d {
	public:
		Vector2d() :x(0), y(0) {}
		Vector2d(const real x, const real y) :x(x), y(y) {}
		/// Adds the given vector to this.
		/// 加上给定向量。
		void operator+=(const Vector2d &v) {
			x += v.x;
			y += v.y;
		}
		/// Subtracts the given vector from this.
		/// 减去给定向量。
		void operator-=(const Vector2d &v) {
			x -= v.x;
			y -= v.y;
		}
		/// Adds the given vecto to this, scaled by the given amount.
		/// 加上一个以给定比例缩放的向量。
		void add_scaled_vector(const Vector2d &v, real scale) {
			x += v.x * scale;
			y += v.y * scale;
		}
		/// Calculates and returns a component-wise product of this
		//  vector with the given vector.
		//  计算并返回与给定向量的分量积的拷贝。
		Vector2d component_product(const Vector2d &v) const {
			return Vector2d(v.x*x, v.y*y);
		}
		/// Perform a [component-wise product] with the given vector and
		//  set this vector to its result.
		//  与给定向量进行[分量积]运算。
		void component_product_update(const Vector2d &v) {
			x *= v.x;
			y *= v.y;
		}
		/// Calculates and returns the scalar product of this vector
		//  with the given vector..
		//  求点积(内积[inner product])并返回
		real scalar_product(const Vector2d &v) const {
			return x*v.x + y*v.y;
		}
		/**
		* a.b = |a||b|*cosθ
		* θ = arccos((a.b)/(|a||b|))
		**/
		/// Calculates and returns the scalar product of this vector
		//  with the given vector.
		//  求点积(内积[inner product])并返回
		real operator*(const Vector2d &v) const {
			return x*v.x + y*v.y;
		}
		/// Multiplies this vector by the givenn scalar
		/// 由给定的标量乘以该向量。
		void operator*=(const real value) {
			x *= value;
			y *= value;
		}
		/// Returns a copy of this vector scaled to the given value.
		/// 返回该向量与给定的标量的乘积的拷贝。
		Vector2d operator*(const real value) const {
			return Vector2d(x*value, y*value);
		}
		/// Gets the magnitude of this vector.
		/// 获取此向量的模。
		real magnitude() const {
			return std::sqrt(x*x +y*y);
		}
		/// Gets the squared magnitude of this vector.
		/// 获取此向量的平方大小。
		real squared_magnitude() const {
			return x*x + y*y;
		}
		/// Turns a [[non-zero]] vector into a vector of unit length.
		/// 将【非零】向量单位化。
		void normalize() {
			real l = magnitude();
			if(l > 0) {
				(*this) *= ((real)1) / l;
			}
		}
		/// Flips all the components of the vector.
		/// 翻转向量
		void invert() {
			x = -x;
			y = -y;
		}
	private:
		/// Hold the value along the x axis
		real x;
		/// Hold the value along the y axis
		real y;
	};
}
#endif
