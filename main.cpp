#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "gravityObject.h"
using namespace std;

#define WIDTH 1920
#define HEIGHT 1080

const float FPS = 30;

vector <gravityObject> gravityObjects;


void update(){

	al_clear_to_color(al_map_rgb(255, 255, 255));

	//calculating new forces for each object
	for(int i = 0; i < gravityObjects.size(); i++){

		gravityObjects[i].force.x = 0;
		gravityObjects[i].force.y = 0;

		for(int j = 0; j < gravityObjects.size(); j++){
			if(i != j) 
				gravityObjects[i].calculateForceToOtherObject(
					gravityObjects[j].mass,
					gravityObjects[j].position
				);
		}
	}

	//update objects to theirs new positions
	for(int i = 0; i < gravityObjects.size(); i++){
		gravityObjects[i].objectUpdate();
	}

	al_flip_display();
}

void getDataFromFile(){
	for(string line; getline(cin,line); )   //read stream line by line
	{
    	istringstream in(line);  //make a stream for the line itself
    	string name;
    	in >> name;   //read name of planet
		
        double mass, posX, posY,spdX,spdY;
		int colR,colG,colB,size;

		//now read the whitespace-separated floats and ints
        in >> mass >> posX >> posY >> spdX >> spdY >> colR >> colG >> colB >> size;

		Vector tmpSpd,tmpPos;
		tmpPos.x = posX; tmpPos.y = posY;
		tmpSpd.x = spdX; tmpSpd.y = spdY;

		Color tmpColor;
		tmpColor.r = colR; tmpColor.g = colG; tmpColor.b = colB;

		gravityObject planet(name, mass, tmpPos, tmpSpd, tmpColor, size);
		gravityObjects.push_back(planet);
	}
}

int main(int argc, char *argv[]){
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	bool running = true;
	getDataFromFile();
	// Initialize allegro
	if (!al_init()) {
		fprintf(stderr, "Failed to initialize allegro.\n");
		running = false;
		return 1;
	}

	// Initialize the timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "Failed to create timer.\n");
		running = false;
		return 1;
	}

	// Create the display
	display = al_create_display(WIDTH, HEIGHT);
	if (!display) {
		fprintf(stderr, "Failed to create display.\n");
		running = false;
		return 1;
	}

	// Create the event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "Failed to create event queue.");
		running = false;
		return 1;
	}
	
	// Register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	//load screen the first time
	update();

	// Start the timer
	al_start_timer(timer);

	while(running){
		
		ALLEGRO_EVENT ev;
		ALLEGRO_TIMEOUT timeout;

		al_init_timeout(&timeout, 10);

		bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

      	// Handle the events
		if (get_event) {
			switch (ev.type) {
				case ALLEGRO_EVENT_TIMER:
					update();
					break;
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					running = false;
					break;
				default:
					fprintf(stderr, "Unsupported event received: %d\n", ev.type);
					break;
			}
		}
	}

	// Clean up after program has finished
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}