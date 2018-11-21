#include <string>

struct Vector {
  double x,y;  
}; 

struct Color {
	int r,g,b;
};


class gravityObject{
    public:
        gravityObject(std::string sName, double sMass, Vector sPosition, Vector sSpeed, Color sColor, int sSize);

    	Vector position;
		Vector speed;
		Vector force;

		Color color;

		int size;
		double mass;

		std::string name;

        void objectUpdate();
        void calculateForceToOtherObject(double otherMass, Vector otherPosition);
};