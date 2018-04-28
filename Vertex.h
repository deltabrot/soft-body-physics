#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <SDL.h>

class Vertex{
	public:
		float x, y, xv, yv, xf, yf, mass;
		Vertex(float x, float y, float mass);
		Vertex();
		void draw(SDL_Renderer * renderer);
		void resetForce();
		void addForce(float xf, float yf);
		void epoch(float epoch);
};

#endif /* __VERTEX_H__ */
