#ifndef __SPRING_H__
#define __SPRING_H__

#include <SDL.h>
#include "Vertex.h"

class Spring{
	public:
		Vertex * v1, * v2;
		float stiffness, length;
		Spring(Vertex & v1, Vertex & v2, float stiffness, float length);
		Spring(Vertex & v1, Vertex & v2, float stiffness);
		Spring(Vertex & v1, Vertex & v2);
		Spring();
		void draw(SDL_Renderer * renderer);
		void addForce();
};

#endif /* __SPRING_H__ */
