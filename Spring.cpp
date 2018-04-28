#include <iostream>
#include <cmath>
#include <SDL.h>
#include "Spring.h"
#include "Vertex.h"
#include "VectorMath.h"

Spring::Spring(Vertex & v1, Vertex & v2, float stiffness, float length){
	this->v1 = &v1;
	this->v2 = &v2;
	this->stiffness = stiffness;
	this->length = length;
}
Spring::Spring(Vertex & v1, Vertex & v2, float stiffness){
	this->v1 = &v1;
	this->v2 = &v2;
	this->stiffness = stiffness;
	this->length = std::abs(sqrt(pow(this->v1->x - this->v2->x,2) + pow(this->v1->y - this->v2->y,2)));
}
Spring::Spring(Vertex & v1, Vertex & v2){
	this->v1 = &v1;
	this->v2 = &v2;
	this->stiffness = 1;
	this->length = std::abs(sqrt(pow(this->v1->x - this->v2->x,2) + pow(this->v1->y - this->v2->y,2)));
}
Spring::Spring(){
	this->stiffness = 1;
}
void Spring::draw(SDL_Renderer * renderer){
	SDL_RenderDrawLine(renderer, v1->x, v1->y, v2->x, v2->y);
}
void Spring::addForce(){
	float currentLength = sqrt(pow(this->v1->x - this->v2->x,2) + pow(this->v1->y - this->v2->y,2));
	float totalForce = stiffness*(currentLength-length);
	float angle = VectorMath::angle(v1->x, v1->y, v2->x, v2->y);
	v1->addForce(totalForce*sinf(angle), totalForce*cosf(angle));
	v2->addForce(-totalForce*sinf(angle), -totalForce*cosf(angle));
}
