#include "c2Pfgen.h"
namespace chis {
	void Particle_force_registry::add(Particle *particle, Particle_force_generator *fg) {
		registrations.push_back({ particle, fg });
	}
	void Particle_force_registry::remove(Particle *particle, Particle_force_generator *fg) {
		for(auto i = registrations.begin(); i != registrations.end(); ++i) {
			if(i->particle == particle && i->fg == fg) {
				registrations.erase(i);
				return;
			}
		}
	}
	void Particle_force_registry::clear() {
		registrations.clear();
	}
	void Particle_force_registry::update_force(real duration) {
		for(auto &i : registrations) {
			i.fg->update_force(i.particle, duration);
		}
	}
	void Particle_gravity::update_force(Particle *particle, real duration) {
		// Check that we do not have infinite mass.
		if(particle->has_infmass()) {
			return;
		}
		// Apply the mass-scaled force to the particle.
		particle->add_force(gravity * particle->get_mass());
	}
	void Particle_drag::update_force(Particle *particle, real duration) {
		Vector2d force;
		force = particle->get_velocity();
		// Calculate the total drag coefficient.
		real drag_coeff = force.magnitude();
		drag_coeff = k1 * drag_coeff + k2 * drag_coeff * drag_coeff;
		// Calculate the final force and apply it.
		force.normalize();
		force *= -drag_coeff;
		particle->add_force(force);
	}
}