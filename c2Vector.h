#ifndef CHIS2D_MATH
#define CHIS2D_MATH
#include <cmath>
#define MAXN 1000
#define offset 10000
#define eps 1e-8
#define PI 3.14159265358979323846//acos(-1.0)
//�ж�һ�����Ƿ�Ϊ0,���򷵻�true,���򷵻�false
#define zero(x)(((x)>0?(x):-(x))<eps)
//����һ�����ķ��ţ���������1����������2�����򷵻�0
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
		/// ���ϸ���������
		void operator+=(const Vector2d &v) {
			x += v.x;
			y += v.y;
		}
		/// Subtracts the given vector from this.
		/// ��ȥ����������
		void operator-=(const Vector2d &v) {
			x -= v.x;
			y -= v.y;
		}
		/// Adds the given vecto to this, scaled by the given amount.
		/// ����һ���Ը����������ŵ�������
		void add_scaled_vector(const Vector2d &v, real scale) {
			x += v.x * scale;
			y += v.y * scale;
		}
		/// Calculates and returns a component-wise product of this
		//  vector with the given vector.
		//  ���㲢��������������ķ������Ŀ�����
		Vector2d component_product(const Vector2d &v) const {
			return Vector2d(v.x*x, v.y*y);
		}
		/// Perform a [component-wise product] with the given vector and
		//  set this vector to its result.
		//  �������������[������]���㡣
		void component_product_update(const Vector2d &v) {
			x *= v.x;
			y *= v.y;
		}
		/// Calculates and returns the scalar product of this vector
		//  with the given vector..
		//  ����(�ڻ�[inner product])������
		real scalar_product(const Vector2d &v) const {
			return x*v.x + y*v.y;
		}
		/**
		* a.b = |a||b|*cos��
		* �� = arccos((a.b)/(|a||b|))
		**/
		/// Calculates and returns the scalar product of this vector
		//  with the given vector.
		//  ����(�ڻ�[inner product])������
		real operator*(const Vector2d &v) const {
			return x*v.x + y*v.y;
		}
		/// Multiplies this vector by the givenn scalar
		/// �ɸ����ı������Ը�������
		void operator*=(const real value) {
			x *= value;
			y *= value;
		}                                                                   
		/// Returns a copy of this vector scaled to the given value.
		/// ���ظ�����������ı����ĳ˻��Ŀ�����
		Vector2d operator*(const real value) const {
			return Vector2d(x*value, y*value);
		}
		/// Gets the magnitude of this vector.
		/// ��ȡ��������ģ��
		real magnitude() const {
			return std::sqrt(x*x +y*y);
		}
		/// Gets the squared magnitude of this vector.
		/// ��ȡ��������ƽ����С��
		real squared_magnitude() const {
			return x*x + y*y;
		}
		/// Turns a [[non-zero]] vector into a vector of unit length.
		/// �������㡿������λ����
		void normalize() {
			real l = magnitude();
			if(l > 0) {
				(*this) *= ((real)1) / l;
			}
		}
		/// Flips all the components of the vector.
		/// ��ת����
		void invert() {
			x = -x;
			y = -y;
		}
	//private:
		/// Hold the value along the x axis
		real x;
		/// Hold the value along the y axis
		real y;
	};
}
#endif