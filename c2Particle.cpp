#include "c2Particle.h"

namespace chis {
	void Particle::integrate(real duration) {
		assert(duration > 0.0);
		
		// Update linear position.
		position.add_scaled_vector(velocity, duration);

		// Work out the acceleration from the force.
		Vector2d resulting_acc = acceleration;
		resulting_acc.add_scaled_vector(force_accum, inverse_mass);

		// Update linear velocity from the acceleration.
		velocity.add_scaled_vector(resulting_acc, duration);

		// Impose drag
		velocity *= std::pow(damping, duration);
	}
}