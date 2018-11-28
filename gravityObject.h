#include <string>

struct Vector {
  double x,y;  
}; 

struct Color {
	int r,g,b;
};


class GravityObject{
    public:
        GravityObject(std::string sName, double sMass, Vector sPosition, Vector sSpeed, Color sColor, int sSize);

    	Vector position;
		Vector speed;
		Vector force;

		Color color;

		int size;
		double mass;

		std::string name;

		//update speed and position of the object and also draw it
        void objectUpdate();

		//calculate force to other object and the add to force vector
        void calculateForceToOtherObject(double otherMass, Vector otherPosition);

		//resets object's force to zero
		void resetForce();
};