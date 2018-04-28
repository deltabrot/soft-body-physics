#include <iostream>
#include <SDL.h>
#include <ctime>
#include "vertex.h"
#include "spring.h"
#include "vectormath.h"
#include "shape.h"

bool init();
void kill();
bool loop();
void drawTriangle(float, float, float, float, float, float);

SDL_Window* window;
SDL_Renderer* renderer;

const int WIDTH=640, HEIGHT=WIDTH*3/4;
clock_t current_ticks = clock(), delta_ticks;
clock_t fps = 0;
int fpsRate = 100000;
int oldClock = clock();
float x = 0;

const float EPOCH = 0.1f;
const int VERTICES = 3;
Vertex vertex[VERTICES], center, mouseVertex;
Vertex * attached;
Spring spring[VERTICES], centerSpring[VERTICES], attachedSpring;
float xPos = 300, yPos = 300;
float totalMass = 0.1f;
int graphicsMode = 0;
Shape shape1;

int main(int argc, char** args) {
        if (!init()){
		return 1;
	}
	
	shape1.createRing(200,200,100,20,2);
	shape1.createRing(200,200,80,20,2,-2*M_PI/40);
	shape1.createVertex(200,200,0.1f);
	shape1.connectLayer(0, 2);
	shape1.connectLayer(1, 2);
	shape1.connectRings(0, 1, 3, 0);
	shape1.connectRings(0, 1, 3, 1);
	shape1.connectVertexToRing(2, 1, 0.5f);

        while ( loop() ) {
		delta_ticks = clock() - current_ticks;
		if(delta_ticks > 0){
			fps = CLOCKS_PER_SEC / delta_ticks;
		}
		if(clock() - oldClock > fpsRate){
			//std::cout << "FPS: "<< fps << std::endl;
			oldClock = clock();
		}

		current_ticks = clock();
                // wait before processing the next frame
                SDL_Delay(10);
        }

        kill();
        return 0;
}
bool loop() {
        static const unsigned char* keys = SDL_GetKeyboardState( NULL );

        SDL_Event e;
        SDL_Rect r;
        // For mouse rectangle (static to presist between function calls)
        static int mouseX, mouseY;
	static bool mouseDown, mouseDetected;

        // Clear the window to white
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear( renderer );

        // Event loop
        while ( SDL_PollEvent( &e ) != 0 ) {
                switch ( e.type ) {
                        case SDL_QUIT:
                                return false;
                        case SDL_MOUSEBUTTONDOWN:
                                mouseX = e.button.x;
                                mouseY = e.button.y;
				mouseDown = true;
				break;
                        case SDL_MOUSEMOTION:
                                mouseX = e.motion.x;
                                mouseY = e.motion.y;
                                break;
                        case SDL_MOUSEBUTTONUP:
                                mouseX = e.button.x;
				mouseY = e.button.y;
				mouseDown = false;
				mouseDetected = false;
                                break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
        	        		case SDLK_w:
	                        		graphicsMode++;
			                        break;
                		}
				if(graphicsMode > 2){
					graphicsMode = 0;
				}
				break;
                }
        }
	if(mouseDown && !mouseDetected){
		mouseDetected = true;
		mouseVertex = Vertex(mouseX, mouseY, 1);
		float smallestLength = pow(10,10);
		for(int i=0;i<shape1.vertexLayer.size();i++){
			for(int j=0;j<shape1.vertexLayer.at(i).size();j++){
				if(sqrt(pow(shape1.vertexLayer.at(i).at(j).x-mouseX,2)+pow(shape1.vertexLayer.at(i).at(j).y-mouseY,2)) < smallestLength){
					smallestLength = sqrt(pow(shape1.vertexLayer.at(i).at(j).x-mouseX,2)+pow(shape1.vertexLayer.at(i).at(j).y-mouseY,2));
					attached = &shape1.vertexLayer.at(i).at(j);
				}
			}
		}
		attachedSpring = Spring(*attached, mouseVertex, 1.0f);
	}
        // Set drawing color to black
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	if(mouseDown){
		attachedSpring.v2->x = mouseX;
		attachedSpring.v2->y = mouseY;
		attachedSpring.addForce();
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		attachedSpring.draw(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
	shape1.epoch(EPOCH);
	shape1.draw(renderer, graphicsMode);

	SDL_RenderPresent( renderer );
	
        return true;
}


bool init() {
        // See last example for comments
        if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
                std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
                system("pause");
                return false;
        }

        window = SDL_CreateWindow( "Isometry", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
        if ( !window ) {
                std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
                system("pause");
                return false;
        }

        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if ( !renderer ) {
                std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
                return false;
        }

        SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
        SDL_RenderClear( renderer );
        return true;
}

void kill() {
        // Quit
        SDL_DestroyRenderer( renderer );
        SDL_DestroyWindow( window );
        SDL_Quit();
}


