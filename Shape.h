#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <vector>
#include <SDL.h>
#include "Vertex.h"
#include "Spring.h"

class Shape{
	public:
		std::vector< std::vector<Vertex> > vertexLayer;
		std::vector<Spring> spring;
		Shape();
		void createRing(float xCenter, float yCenter, float radius, int numVertices, float mass);
		void createRing(float xCenter, float yCenter, float radius, int numVertices, float mass, float rotation);
		void createVertex(float x, float y, float mass);
		void connectLayer(int vl1index, float stiffness);
		void connectRings(int v1index, int v2index, float stiffness, int shift);
		void connectVertexToRing(int v1index, int vl1index, float stiffness);
		void epoch(float epoch);
		void draw(SDL_Renderer * renderer, int mode);
};

#endif /* __SHAPE_H__ */
