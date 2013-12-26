#ifndef MY_CLOCK
#define MY_CLOCK

#include "CGF/CGFobject.h"
#include "myCylinder.h"
#include "myUnitCube.h"
#include "MyClockHand.h"
#include <ctime>
class myClock : public CGFobject {

	private:
		myCylinder* cilindro;
		myClockHand* segundos;
		myClockHand* minutos;
		myClockHand* horas;
		bool activate;

	public:
		myClock();
		void draw();
		void update(unsigned long timelocal);
		void drawponteiros();
		void setActivate(bool state) {activate=state;};
		bool getActivate() {return activate;};
		
};



#endif
