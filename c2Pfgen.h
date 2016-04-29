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
}
#endif