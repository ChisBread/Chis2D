#include "c2Particle.h"
#include "c2Pfgen.h"
#include <graphics.h>
using namespace chis;
void draw1() {
	Particle pa;
	pa.set_position(Vector2d(150, 150));
	pa.set_velocity(Vector2d(-1, -2));

	pa.set_damping(0.997);
	Vector2d posa, posb;
	for(; is_run(); delay_fps(120)) {
		Vector2d f = pa.get_position();
		f -= Vector2d(300, 300);
		f.normalize();
		f *= -5;
		pa.set_force_accum(f);
		posa = pa.get_position();
		pa.integrate(1.0 / 13);
		posb = pa.get_position();
		line(posa.x, posa.y, posb.x, posb.y);
	}
}
void drag() {
	Particle_force_registry pfr;
	Particle_drag pdrag(0.01, 0.02);
	Particle p1;
	p1.set_position({ 0, 150 });
	p1.set_velocity({ 25, 0 });
	pfr.add(&p1, &pdrag);
	for(; is_run(); delay_fps(60)) {
		pfr.update_force(1.0 / 10);
		p1.integrate(1.0 / 10);
		line(p1.get_position().x, p1.get_position().y, 0, 150);
		if((p1.get_velocity().magnitude()) < 0.08) {
			break;
		}
	}
}
void gravity() {
	Particle_force_registry pfr;
	Particle_gravity pgra({0, 5});
	Particle_drag pdrag(0.002,0.004);
	Particle p1;
	p1.set_position({ 0, 150 });
	p1.set_velocity({ 35, 0 });
	pfr.add(&p1, &pgra);
	pfr.add(&p1, &pdrag);
	Vector2d pos;
	for(; is_run(); delay_fps(60)) {
		pos = p1.get_position();
		pfr.update_force(1.0 / 10);
		p1.integrate(1.0 / 10);
		line(p1.get_position().x, p1.get_position().y, pos.x, pos.y);
		if(pos.y > 600) {
			break;
		}
	}
}
int main() {
	initgraph(800, 600);
	gravity();
	//drag();
	getch();
	closegraph();
}