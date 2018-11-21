#include "gravityObject.h"
#include <math.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include <string>

#define gravityConst 6.67408

gravityObject::gravityObject(std::string sName, double sMass, Vector sPosition, Vector sSpeed, Color sColor, int sSize){
	force.x=0.0;
	force.y=0.0;
	mass = sMass;
	position = sPosition;
	speed = sSpeed;
	color = sColor;
	size = sSize;
	name = sName;
}

void gravityObject::objectUpdate(){
	speed.x = speed.x + (force.x / mass) * pow(10,-5);
	speed.y = speed.y + (force.y / mass) * pow(10,-5);
	position.x = position.x + speed.x;
	position.y = position.y + speed.y;

	al_draw_filled_circle(position.x, position.y, size, al_map_rgb(color.r, color.g, color.b));
}

void gravityObject::calculateForceToOtherObject(double otherMass, Vector otherPosition){
	double distSquared = pow(otherPosition.x-position.x,2)+pow(otherPosition.y-position.y,2);

	double forceMag = (gravityConst * pow(10,5) * (otherMass * mass)) / distSquared;
	double angleCos =  (otherPosition.x-position.x) / sqrt(distSquared);
	double angleSin =  (otherPosition.y-position.y) / sqrt(distSquared);
	force.x += forceMag * angleCos;
	force.y += forceMag * angleSin;
}
