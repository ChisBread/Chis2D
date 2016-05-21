#ifndef CHIS2D_PFGEN
#define CHIS2D_PFGEN
#include "c2Vector.h"
#include <vector>
#include "c2Particle.h"
namespace chis {
	/**
	* A force generator can be asked to add a force to one or more
	* particles.
	**/
	class Particle_force_generator {
	public:
		/**
		* Overload this in implementations of the interface to calculate
		* and update the force applied to the given particle.
		**/
		virtual void update_force(Particle *particle, real duration) = 0;
	};
	class Particle_force_registry {
	protected:
		/**
		* Keeps track of one force generator and the particle it
		* applies to.
		**/
		struct _particle_force_registration {
			Particle *particle;
			Particle_force_generator *fg;
		};
		/**
		* Holds the list of registrations.
		**/
		using Registry = std::vector<_particle_force_registration>;
		Registry registrations;
	public:
		/**
		* Registers the given force generator to apply to the
		* given particle.
		**/
		void add(Particle *particle, Particle_force_generator *fg);
		/**
		* Removes the given registered pair from the registry.
		* If the pair is not registered, this method will have
		* no effect.
		**/
		void remove(Particle *particle, Particle_force_generator *fg);
		/**
		* Clears all registrations from the registry. This will
		* not delete the particles or the force generators
		* themselves, just the records of their connection.
		**/
		void clear();
		/**
		* Calls all the force generators to update the forces of
		* their corresponding particles.
		**/
		void update_force(real duration);
	};
	class Particle_gravity : public Particle_force_generator {
	public:
		/**
		* Creates the generator with the given acceleration.
		**/
		Particle_gravity(const Vector2d &gravity) :gravity(gravity) {}
		/***
		* Applies the gravitational force to the given particle.
		*/
		virtual void update_force(Particle *particle, real duration);
	private:
		Vector2d gravity;
	};

	/**
	* A force generator that applies a drag force. One instance
	* can be used for multiple particles.
	**/
	class Particle_drag :public Particle_force_generator {
	public:
		/**
		* Creates the generator with the given coefficient.
		**/
		Particle_drag(real k1, real k2) :k1(k1), k2(k2) {}
		/**
		* Applies the drag force to the given particle
		**/
		virtual void update_force(Particle *particle, real duration);
	private:
		/**
		* Holds the velocity drag coefficient 
		* and velocity squared drag coefficient.
		**/
		real k1, k2;
	};
	/**
	* A force generator that applies a spring force.
	**/
	class Particle_spring :public Particle_force_generator {
	public:
		/**
		* Creates a new spring with the given parameters.
		**/
		Particle_spring(Particle *other, 
			real spring_constant, real rest_length) 
			:other(other), spring_constant(spring_constant), rest_length(rest_length) { }
		/**
		* Applies the spring force to the given particle.
		**/
		virtual void update_force(Particle *particle, real duration);
	private:
		/// The particle at the other end of the spring.
		Particle *other;
		/// Holds the spring constant.
		real spring_constant;
		/// Holds the rest length of the spring.
		real rest_length;
	};
	class Particle_anchored_spring : public Particle_force_generator {
	public:
		/**
		* Creates a new spring with the given parameters.
		**/
		Particle_anchored_spring(Vector2d *anchor,
			real spring_constant, real rest_length)
			:anchor(anchor), spring_constant(spring_constant), rest_length(rest_length) { }
		/**
		* Applies the spring force to the given particle.
		**/
		virtual void update_force(Particle *particle, real duration);
	private:
		/// The location of the anchored end of the spring.
		Vector2d *anchor;
		/// Holds the spring constant.
		real spring_constant;
		/// Holds the rest length of the spring.
		real rest_length;
	};

	class Particle_bungee : public Particle_force_generator {
	public:
		/**
		* Creates a new spring with the given parameters.
		**/
		Particle_bungee(Particle *other,
			real spring_constant, real rest_length)
			:other(other), spring_constant(spring_constant), rest_length(rest_length) {
		}
		/**
		* Applies the spring force to the given particle.
		**/
		virtual void update_force(Particle *particle, real duration);
	private:
		/// The particle at the other end of the spring.
		Particle *other;
		/// Holds the spring constant.
		real spring_constant;
		/// Holds the rest length of the spring.
		real rest_length;
	};
	class Particle_anchored_bungee : public Particle_force_generator {
	public:
		/**
		* Creates a new spring with the given parameters.
		**/
		Particle_anchored_bungee(const Vector2d *anchor,
			real spring_constant, real rest_length)
			:anchor(anchor), spring_constant(spring_constant), rest_length(rest_length) {
		}
		/**
		* Applies the spring force to the given particle.
		**/
		virtual void update_force(Particle *particle, real duration);
	private:
		/// The location of the anchored end of the spring.
		const Vector2d *anchor;
		/// Holds the spring constant.
		real spring_constant;
		/// Holds the rest length of the spring.
		real rest_length;
	};
	/**
	* A force generator that fakes a stiff spring force, and where
	* one end is attached to a fixed point in space.
	**/
	class Particle_fake_spring :public Particle_force_generator {
	public:
		/**
		* Creates a new spring with the given parameters.
		**/
		Particle_fake_spring(const Vector2d *anchor,
			real spring_constant, real damping)
			:anchor(anchor), spring_constant(spring_constant), damping(damping) {
		}
		/**
		* Applies the spring force to the given particle.
		**/
		virtual void update_force(Particle *particle, real duration);
	private:
		/**
		* The location of the anchored end of the spring.
		**/
		const Vector2d *anchor;
		/**
		* Holds the spring constant.
		**/
		real spring_constant;
		/**
		* Holds the damping on the oscillation of the spring.
		**/
		real damping;
	};
}
#endif