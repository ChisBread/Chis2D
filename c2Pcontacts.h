#ifndef CHIS_PCONTACTS
#define CHIS_PCONTACTS
#include "c2Particle.h"
namespace chis {
	class Particle_contact {
	public:
		/**
		* Holds the particles that are involved in the contact. the
		* second of these can be NULL, for contacts with the scenery.
		**/
		Particle *particle[2];
		/**
		* Holds the normal restitution coefficient at the contact.
		**/
		real restitution;
		/**
		* Holds the direction of the contact in world coordinates.
		**/
		Vector2d contact_normal;
	protected:
		/**
		* Resolves this contact, for both velocity and interpenetration.
		**/
		void resolve(real duration);
		/**
		* Calculates the separating velocity at this contact.
		**/
		real calculate_separating_velocity() const;
	private:
		/**
		* Handles the impulse calculations for this collision.
		**/
		void resolve_velocity(real duration);
	};
}
#endif