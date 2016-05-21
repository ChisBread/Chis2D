#include "c2Particle.h"
#include "c2Pfgen.h"
#include <graphics.h>
#include <list>
#include <cstdlib>
using namespace chis;
void draw1() {
	Particle pa;
	pa.set_position(Vector2d(150, 150));
	pa.set_velocity(Vector2d(-5, -2));

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
	Particle p1;
	p1.set_position({ 0, 150 });
	p1.set_velocity({ 35, 0 });
	pfr.add(&p1, &pgra);
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
void spring() {
	Particle_force_registry pfr;
	Particle p1, p2;
	Particle_spring psp1(&p2, 0.1, 50);
	Particle_spring psp2(&p1, 0.1, 50);
	p2.set_position({ 20, 150 });
	//p2.set_mass(0.5);
	p1.set_position({ 90, 150 });
	p1.set_velocity({ 0, 0 });
	pfr.add(&p1, &psp1);
	pfr.add(&p2, &psp2);
	for(; is_run(); delay_fps(180)) {
		pfr.update_force(1.0 / 10);
		p1.integrate(1.0 / 30);
		p2.integrate(1.0 / 30);
		cleardevice();
		line(p1.get_position().x, p1.get_position().y, p2.get_position().x, p2.get_position().y);
	}
}
void fake_spring() {
	Particle_force_registry pfr;
	Particle p1, p2;
	Particle_fake_spring psp1(&p2.get_position(), 0.3, p2.get_damping());
	Particle_fake_spring psp2(&p1.get_position(), 0.3, p1.get_damping());
	p2.set_position({ 50, 150 });
	p1.set_position({ 90, 150 });
	pfr.add(&p1, &psp1);
	pfr.add(&p2, &psp2);
	for(; is_run(); delay_fps(180)) {
		pfr.update_force(1.0 / 300);
		p1.integrate(1.0 / 300);
		p2.integrate(1.0 / 300);
		cleardevice();
		line(p1.get_position().x, p1.get_position().y, p2.get_position().x, p2.get_position().y);
	}
}
void net() {
	const double K = 0.4, L = 15;
	const int N = 25;
	Particle_force_registry pfr;
	Particle_drag pdrag(0.03, 0.02);
	Particle net[N][N];
	using T = Particle_bungee;
	std::list<T> pss;
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			net[i][j].set_position({ (i)*L + 80, (j)*L + 80});
			net[i][j].set_velocity({ 20, 26 });
			net[i][j].set_acceleration({ 0, 10 });
			net[i][j].set_mass(0.007);
			pfr.add(&net[i][j], &pdrag);
		}
	}

	//net[N-1][N-1].set_velocity({ 5, 10 });
	//net[N-1][0].set_velocity({ -5, 10 });
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			if(i - 1 >= 0) {
				pss.push_back(T(&net[i - 1][j], K, L));
				pfr.add(&net[i][j], &pss.back());
			}
			if(i + 1 < N) {
				pss.push_back(T(&net[i + 1][j], K, L));
				pfr.add(&net[i][j], &pss.back());
			}
			if(j - 1 >= 0) {
				pss.push_back(T(&net[i][j - 1], K, L));
				pfr.add(&net[i][j], &pss.back());
			}
			if(j + 1 < N) {
				pss.push_back(T(&net[i][j + 1], K, L));
				pfr.add(&net[i][j], &pss.back());
			}
		}
	}
	for(; is_run(); delay_fps(600)) {
		pfr.update_force(1.0 / 50);
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				if(j == 0 &&(i == 0 || i == N / 2 || i == N - 1)) {
					continue;
				}
				net[i][j].integrate(1.0 / 50);
			}
		}
		cleardevice();
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				circle(net[i][j].get_position().x, net[i][j].get_position().y, 2);
				if(i - 1 >= 0) {
					line(net[i - 1][j].get_position().x, net[i - 1][j].get_position().y
						, net[i][j].get_position().x, net[i][j].get_position().y);
				}
				if(i + 1 < N) {
					line(net[i + 1][j].get_position().x, net[i + 1][j].get_position().y
						, net[i][j].get_position().x, net[i][j].get_position().y);
				}
				if(j - 1 >= 0) {
					line(net[i][j - 1].get_position().x, net[i][j - 1].get_position().y
						, net[i][j].get_position().x, net[i][j].get_position().y);
				}
				if(j + 1 < N) {
					line(net[i][j + 1].get_position().x, net[i][j + 1].get_position().y
						, net[i][j].get_position().x, net[i][j].get_position().y);
				}
			}
		}
	}
}
int main() {
	initgraph(800, 600);
	fake_spring();
	net();
	//gravity();
	//spring();
	//drag();
	//draw1();
	getch();
	closegraph();
}