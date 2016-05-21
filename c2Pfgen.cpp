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
	void Particle_spring::update_force(Particle *particle, real duration) {
		// Calculate the vector of the spring.
		Vector2d force;
		force = particle->get_position();
		force -= other->get_position();

		// Calculate the magnitude of the force.
		real magnitude = force.magnitude();
		magnitude = rest_length - magnitude;
		magnitude *= spring_constant;

		// Calculate the final force and apply it.
		force.normalize();
		force *= magnitude;
		particle->add_force(force);
	}
	void Particle_anchored_spring::update_force(Particle *particle, real duration) {
		Vector2d force;
		force = particle->get_position();
		force -= *anchor;

		// Calculate the magnitude of the force.
		real magnitude = force.magnitude();
		magnitude = magnitude - rest_length;
		magnitude *= spring_constant;

		// Calculate the final force and apply it.
		force.normalize();
		force *= -magnitude;
		particle->add_force(force);
	}
	void Particle_bungee::update_force(Particle *particle, real duration) {
		// Calculate the vector of the spring.
		Vector2d force;
		force = particle->get_position();
		force -= other->get_position();

		// Calculate the magnitude of the force.
		real magnitude = force.magnitude();
		if(magnitude <= rest_length) {
			return;
		}
		magnitude = spring_constant*(rest_length - magnitude);

		// Calculate the final force and apply it.
		force.normalize();
		force *= magnitude;
		particle->add_force(force);
	}
	void Particle_anchored_bungee::update_force(Particle *particle, real duration) {
		Vector2d force;
		force = particle->get_position();
		force -= *anchor;

		// Calculate the magnitude of the force.
		real magnitude = force.magnitude();
		if(magnitude <= rest_length) {
			return;
		}
		magnitude = magnitude - rest_length;
		magnitude *= spring_constant;

		// Calculate the final force and apply it.
		force.normalize();
		force *= -magnitude;
		particle->add_force(force);
	}
	void Particle_fake_spring::update_force(Particle *particle, real duration) {
		//Check that we do not have infinite mass.
		if(particle->has_infmass()) {
			return;
		}
		// Calculate the relative position of the particle to anchor.
		Vector2d position = particle->get_position();
		position -= *anchor;

		// Calculate the constants and check whether they are in bounds.
		real gamma = 0.5 * std::sqrt(4 * spring_constant - damping*damping);
		if(gamma == 0.0) {
			return;
		}
		Vector2d c = position * (damping / (2.0 * gamma)) 
			+ particle->get_velocity() * (1.0 / gamma);
		// Calculate the target position.
		Vector2d target = position * std::cos(gamma * duration)
			+ c * std::sin(gamma * duration);
		target *= std::exp(-0.5 * duration * damping);

		// Calculate the resulting acceleration and thereforce the force.
		Vector2d accel = (target - position) * (1.0 / (duration*duration)) 
			- particle->get_velocity() * duration;
		//accel.invert();
		particle->add_force(accel * particle->get_mass());
	}
}