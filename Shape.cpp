#include <iostream>
#include <cmath>
#include <vector>
#include "Vertex.h"
#include "Spring.h"
#include "Shape.h"

Shape::Shape(){
}

void Shape::createRing(float xCenter, float yCenter, float radius, int numVertices, float mass){
	createRing(xCenter, yCenter, radius, numVertices, mass, 0);
}
void Shape::createRing(float xCenter, float yCenter, float radius, int numVertices, float mass, float rotation){
	std::vector<Vertex> ring;
	for(int i=0; i<numVertices; i++){
		ring.push_back(Vertex(xCenter+(radius*cosf((2*M_PI*i/numVertices)+rotation)), yCenter+(radius*sinf((2*M_PI*i/numVertices)+rotation)), mass/numVertices));
	}
	vertexLayer.push_back(ring);
}
void Shape::createVertex(float x, float y, float mass){
	std::vector<Vertex> singleVertex;
	singleVertex.push_back(Vertex(x,y,mass));
	vertexLayer.push_back(singleVertex);
}
void Shape::connectLayer(int vl1index, float stiffness){
	for(int i=0;i<vertexLayer.at(vl1index).size();i++){
                spring.push_back(Spring(vertexLayer.at(vl1index).at(i),vertexLayer.at(vl1index).at((i+1)%vertexLayer.at(vl1index).size()), stiffness));
        }
}
void Shape::connectRings(int vl1index, int vl2index, float stiffness, int shift){
	for(int i=0;i<vertexLayer.at(vl1index).size();i++){
		spring.push_back(Spring(vertexLayer.at(vl1index).at(i),vertexLayer.at(vl2index).at((i+shift)%vertexLayer.at(vl1index).size()), stiffness));
	}
}
void Shape::connectVertexToRing(int v1index, int vl1index, float stiffness){
	for(int i=0;i<vertexLayer.at(vl1index).size();i++){
		spring.push_back(Spring(vertexLayer.at(v1index).at(0), vertexLayer.at(vl1index).at(i), stiffness));
	}
}
void Shape::epoch(float epoch){
	for(int i=0;i<spring.size();i++){
        	spring.at(i).addForce();
        }
	for(int i=0;i<vertexLayer.size();i++){
                for(int j=0;j<vertexLayer.at(i).size();j++){
                        vertexLayer.at(i).at(j).epoch(epoch);
                }  
        }	
	for(int i=0;i<vertexLayer.size();i++){
                for(int j=0;j<vertexLayer.at(i).size();j++){
			vertexLayer.at(i).at(j).resetForce();
                }  
        }
}
void Shape::draw(SDL_Renderer * renderer, int mode){
	switch(mode){
		case 0:
			for(int i=0;i<vertexLayer.at(0).size();i++){
				spring.at(i).draw(renderer);
			}
			break;
		case 1:
			for(int i=0;i<spring.size();i++){
				spring.at(i).draw(renderer);
			}
			break;
		case 2:
			for(int i=0;i<vertexLayer.size();i++){
				for(int j=0;j<vertexLayer.at(i).size();j++){
					vertexLayer.at(i).at(j).draw(renderer);
				}
			}
			break;
	}
}
