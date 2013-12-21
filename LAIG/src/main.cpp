#include <iostream>
#include <exception>
#include <string>
#include <map>


#include "Node.h"
#include "XMLscene.h"
#include "CGFapplication.h"
#include "TPinterface.h"
using namespace std;  
  
  
int main(int argc, char* argv[]) {
  
    CGFapplication* app = new CGFapplication();

	Game* octi = new Game();

    try {
        app->init(&argc, argv);
		
        if(argc == 1)
		{ 
			app->setScene(new XMLScene("octi1.xml",app,octi)); 
		} 
		else
		{ 
			
			app->setScene(new XMLScene(argv[1],app,octi)); 
		}
        app->setInterface(new TPinterface(octi));
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