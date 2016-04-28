#ifndef CHIS2D_PARTICLE
#define CHIS2D_PARTICLE
#include <cassert>
#include "c2Vector.h"
namespace chis {
	/**
	* A Particle is the simplest object that can be simulated in the
	* physics system.
	**/
	class Particle {
	public:
		Particle() :damping(0.995),inverse_mass(1) { }
		/**
		* Integrates the particle forward in time by the given amount
		* This function uses a Newton-Euler integration method, which is a
		* linear approximation of the correct integral. For this reason it
		* may be inaccurate in some cases
		**/
		/// ���ƻ���
		void integrate(real duration);
		void set_position(Vector2d p) {
			position = p;
		}
		void set_velocity(Vector2d v) {
			velocity = v;
		}
		void set_acceleration(Vector2d a) {
			acceleration = a;
		}
		void set_force_accum(Vector2d fa) {
			force_accum = fa;
		}
		void set_damping(real d) {
			damping = d;
		}
		void set_inverse_mass(real im) {
			inverse_mass = im;
		}
		void set_mass(real m) {
			inverse_mass = 1 / m;
		}

		const Vector2d& get_position() const {
			return position;
		}
		const Vector2d& get_velocity() const {
			return velocity;
		}
		const Vector2d& get_acceleration() const {
			return acceleration;
		}
		const Vector2d& get_force_accum() const {
			return force_accum;
		}
		real get_damping() const {
			return damping;
		}
		real get_inverse_mass() const {
			return inverse_mass;
		}
		real get_mass() const{
			assert(!(zero(inverse_mass)));
			return 1 / inverse_mass;
		}
	private:
		/**
		* Holds the linear position of the particle in
		* world space.
		**/
		/// ��������
		Vector2d position;
		/**
		* Holds the linear velocity of the particle in
		* world space.
		**/
		/// �ٶ�
		Vector2d velocity;
		/**
		* Holds the acceleration of the particle, This value
		* can be used to set acceleration due to gravity (its primary use)
		* or any other constant acceleration.
		**/
		/// ���ٶ�
		Vector2d acceleration;
		/**
		* Holds the force of the particle.
		**/
		Vector2d force_accum;
		/**
		* Holds the amount of damping applied to linear
		* motion. Damping is requred to remove energy added
		* through numerical istability in the integrator.
		**/
		/// ����ϵ��
		//  ���������� 0.995
		real damping;
		/**
		* Holds the inverse of the mass (1/m) of the particle. It
		* is more useful to hold the inverse mass because
		* integration is simpler and because in real-time
		* simulation it is more useful to have objects with
		* infinite mass (immovable) than zero mass
		* (completely unstable in numerical simulation).
		**/
		/// �����ĵ���
		//  ���ǵ�0������������������Լ�����Ч�� (a = (1/m)*f)
		//  ʹ�������ĵ�����һ�����ǵ�ѡ��.
		real inverse_mass;
	};
}
#endif