#include <iostream>
#include <cmath>
#include <SDL.h>
#include "Vertex.h"

Vertex::Vertex(float x, float y, float mass){
	this->x = x;
	this->y = y;
	this->mass = mass;
	xf = yf = xv = yv = 0;
}

Vertex::Vertex(){
	Vertex(0, 0, 1);
}
void Vertex::draw(SDL_Renderer * renderer){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}
void Vertex::resetForce(){
	xf = yf = 0;
}
void Vertex::addForce(float xf, float yf){
	this->xf += xf;
	this->yf += yf;
}
void Vertex::epoch(float epoch){
	xv += epoch*xf/mass;
	yv += epoch*yf/mass;
	yv -= 0.3;
	x += (xv*epoch) + xf/mass/2*epoch*epoch;
	y -= (yv*epoch) + yf/mass/2*epoch*epoch;
	float restitution = 0.5f;
	if(x < 0){
		x = 0;
		xv = 0;
		yv *= restitution;
	}
	if(x > 639){
		x = 639;
		xv = 0;
		yv *= restitution;
	}
	if(y < 0){
		y = 0;
		yv = 0;
		xv *= restitution;
	}
	if(y > 479){
		y = 479;
		yv = 0;
		xv *= restitution;
	}
}
