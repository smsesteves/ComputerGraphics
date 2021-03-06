#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <thread> 
#include "Node.h"
#include "XMLscene.h"
#include "CGFapplication.h"
#include "TPinterface.h"
using namespace std;  
  
  
void f1(){
	system(".\\Octi.exe");
}

int main(int argc, char* argv[]) {
  
	thread first (f1);
	

    CGFapplication* app = new CGFapplication();
	Game* octi = new Game();
	octi->setEnded(false);
	

    try {
		app->width = 800;
		app->height = 400;
		//app->xy_aspect = 2;
        app->init(&argc, argv);
		glutReshapeWindow(800,550);

		
        if(argc == 1)
		{ 
			app->setScene(new XMLScene("octi1.xml",app,octi,0)); 
		} 
		else
		{ 
			
			app->setScene(new XMLScene(argv[1],app,octi,0)); 
		}
        app->setInterface(new TPinterface(octi,app));
        app->run();
    }
    catch(GLexception& ex) {
        cout << "Error: " << ex.what();
        return -1;
    }
    catch(exception& ex) {
        cout << "Unexpected error: " << ex.what();
        return -1;
    }
  
    return 0;
}