#include "gravityObject.h"
#include <math.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <string>

#define gravityConst 6.67408

//initialization of variables
GravityObject::GravityObject(std::string sName, double sMass, Vector sPosition, Vector sSpeed, Color sColor, int sSize){
	force.x=0.0;
	force.y=0.0;
	mass = sMass;
	position = sPosition;
	speed = sSpeed;
	color = sColor;
	size = sSize;
	name = sName;
}

void GravityObject::objectUpdate(){
	//increasing speed using new force v=F/m*dt, dt is just next frame
	speed.x = speed.x + (force.x / mass) * pow(10,-5);
	speed.y = speed.y + (force.y / mass) * pow(10,-5);
	//increasing position p = v*dt
	position.x = position.x + speed.x;
	position.y = position.y + speed.y;

	//draw object
	al_draw_filled_circle(position.x, position.y, size, al_map_rgb(color.r, color.g, color.b));
}

void GravityObject::calculateForceToOtherObject(double otherMass, Vector otherPosition){

	//calculate distance to the power of 2 
	double distSquared = pow(otherPosition.x-position.x,2)+pow(otherPosition.y-position.y,2);

	//calculate force according to newtonian equation G*m1*m2/r^2
	double forceMag = (gravityConst * pow(10,5) * (otherMass * mass)) / distSquared;

	//calculate heading (heading of the relative position vector is the same as force's)
	double angleCos =  (otherPosition.x-position.x) / sqrt(distSquared);
	double angleSin =  (otherPosition.y-position.y) / sqrt(distSquared);

	//increase force 
	force.x += forceMag * angleCos;
	force.y += forceMag * angleSin;
}

void GravityObject::resetForce(){
	force.x = 0;
	force.y = 0;
}
