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

//frame rate can be changed(by increasing framerate you also increase simulation speed!)
const float FPS = 30;

vector <GravityObject> gravityObject;


void update(){

	//reset the background
	al_clear_to_color(al_map_rgb(255, 255, 255));

	//calculating new force for each object
	for(int i = 0; i < gravityObject.size(); i++){

		//reset force
		gravityObject[i].resetForce();

		//adding force from every other object
		//loop for every object in the array
		for(int j = 0; j < gravityObject.size(); j++){
			if(i != j)  //checking if the other object is not itself
				gravityObject[i].calculateForceToOtherObject(
					gravityObject[j].mass,
					gravityObject[j].position
				); //calculating the force
		}
	}

	//update objects to theirs new positions and redraw planets
	for(int i = 0; i < gravityObject.size(); i++){
		/*this function cant be in upper loop,
		because position of the object would be changed and then
		other object would calculate theirs forces wrongly*/
		gravityObject[i].objectUpdate();
	}

	//update screen
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

		//generate vectors from read floats
		Vector tmpSpd,tmpPos;
		tmpPos.x = posX; tmpPos.y = posY;
		tmpSpd.x = spdX; tmpSpd.y = spdY;

		//generate color from read ints
		Color tmpColor;
		tmpColor.r = colR; tmpColor.g = colG; tmpColor.b = colB;

		//generate new object and put it into array of object
		GravityObject planet(name, mass, tmpPos, tmpSpd, tmpColor, size);
		gravityObject.push_back(planet);
	}
}

//most of the stuff in main is for allegro library 
int main(int argc, char *argv[]){
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	bool running = true;

	// Initialize allegro
	if (!al_init()) {
		fprintf(stderr, "Failed to initialize allegro.\n");
		return 1;
	}

	// Initialize the timer
	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "Failed to create timer.\n");
		return 1;
	}

	// Create the display
	display = al_create_display(WIDTH, HEIGHT);
	if (!display) {
		fprintf(stderr, "Failed to create display.\n");
		return 1;
	}

	// Create the event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "Failed to create event queue.");
		return 1;
	}

	// Register event sources
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
	//read the planets data
	getDataFromFile();

	//load screen for the first time
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
					update(); //update screen on every new frame
					break;
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					running = false;
					break;
				default:
					break;
			}
		}
	}

	// Clean up after program has finished
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}