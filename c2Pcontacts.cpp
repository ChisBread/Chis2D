#include "c2Pcontacts.h"

namespace chis {
	void Particle_contact::resolve(real duration) {
		resolve_velocity(duration);
	}
	real Particle_contact::calculate_separating_velocity() const {
		Vector2d relative_velocity = particle[0]->get_velocity();
		if(particle[1]) {
			relative_velocity -= particle[1]->get_velocity();
		}
		return relative_velocity * contact_normal;
	}
	void Particle_contact::resolve_velocity(real duration) {
		// Find the velocity in the direction of the contact;
		real separating_velocity = calculate_separating_velocity();
		
		// Check whether it needs to be resolved.
		if(separating_velocity > 0) {
			// The contact is either separating or stationary - there's
			// no impulse required.
			return;
		}

		// Calculate the new separating velocity.
		real new_sep_velocity = -separating_velocity * restitution;
		real delta_velocity = new_sep_velocity - separating_velocity;
		// We apply the change in velocity to each object in proportion to
		// its inverse mass (i.e., those with lower inverse mass [higher
		// actual mass] get less change in velocity).
		real total_inverse_mass = particle[0]->get_inverse_mass();
		if(particle[1]) {
			total_inverse_mass += particle[1]->get_inverse_mass();
		}

		// If all particles have infinite mass, then impulses have no effect.
		if(total_inverse_mass <= 0) {
			return;
		}

		// Calculate the impulse to apply.
		real impulse = delta_velocity / total_inverse_mass;

		// Find the amount of impulse per unit of inverse mass.
		Vector2d impulse_per_imass = contact_normal * impulse;

		// Apply impulses: they are applied in the direction of the contact,
		// and are proportional to the inverse mass.
		particle[0]->set_velocity(particle[0]->get_velocity() +
			impulse_per_imass * particle[0]->get_inverse_mass()
			);
		if(particle[1]) {
			// Particle 1 goes in the opposite direction.
			particle[1]->set_velocity(particle[1]->get_velocity() +
				impulse_per_imass * -particle[1]->get_inverse_mass());
		}
	}
}