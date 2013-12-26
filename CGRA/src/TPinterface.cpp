#include "TPinterface.h"

TPinterface::TPinterface()
{
	testVar=0;
}


void TPinterface::processKeyboard(unsigned char key, int x, int y)
{
	// Uncomment below if you would like to process the default keys (e.g. 's' for snapshot, 'Esc' for exiting, ...)
	CGFinterface::processKeyboard(key, x, y);

	switch(key)
	{
		case 'j':
		{

			// This is an example of accessing the associated scene
			// To test, create the function toggleSomething in your scene to activate/deactivate something
			//((LightingScene *) scene)->toggleSomething();
			((LightingScene*) scene)->rotateRobot(true);
			break;
		}
		case 'l':
		{
			((LightingScene*) scene)->rotateRobot(false);
			break;
		}
		case 'i':
		{
			((LightingScene*) scene)->moveRobot(true);
			break;
		}
		case 'k':
		{
			((LightingScene*) scene)->moveRobot(false);
			break;
		}
	}
}

void TPinterface::initGUI()
{
	// Check CGFinterface.h and GLUI documentation for the types of controls available
	GLUI_Panel *varPanel= addPanel("", 1);
	//addSpinnerToPanel(varPanel, "Val 1(interface)", 2, &testVar, 1);

	int p = 0;
	addCheckboxToPanel(varPanel, "Luz 0", &(((LightingScene*) scene)->lightsState[0]), 0);
	addCheckboxToPanel(varPanel, "Luz 1", &(((LightingScene*) scene)->lightsState[1]), 1);
	addCheckboxToPanel(varPanel, "Luz 2", &(((LightingScene*) scene)->lightsState[2]), 2);
	addCheckboxToPanel(varPanel, "Luz 3", &(((LightingScene*) scene)->lightsState[3]), 3);
	
	addColumnToPanel(varPanel);
	addButtonToPanel(varPanel, "Pausar Relogio", 4);
	addButtonToPanel(varPanel, "Reiniciar Relogio", 5);

	addColumnToPanel(varPanel);
	GLUI_RadioGroup * group1=addRadioGroupToPanel(varPanel,&(((LightingScene*) scene)->mode),6);
	addRadioButtonToGroup(group1,"Wireframe");
	addRadioButtonToGroup(group1,"Fill");


	addColumnToPanel(varPanel);
	
	 GLUI_Listbox * lbRobotText=addListboxToPanel(varPanel,"texturas",&(((LightingScene*) scene)->robottexture),7);
	 lbRobotText->add_item(1,"quadrado");
	 lbRobotText->add_item(2,"madeira");
	 lbRobotText->add_item(3,"paisagem");
	
	
	
	// You could also pass a reference to a variable from the scene class, if public
	//addSpinnerToPanel(varPanel, "Val 2(scene)", 2, &(((LightingScene*) scene)->sceneVar), 2);

}

void TPinterface::processGUI(GLUI_Control *ctrl)
{
	printf ("GUI control id: %d\n  ",ctrl->user_id);
	/*switch (ctrl->user_id)
	{
		case 1:
		{
			printf ("New Val 1(interface): %d\n",testVar);
			break;
		};

		case 2:
		{
			//printf ("New Val 2(scene): %d\n",((LightingScene*) scene)->sceneVar);
			break;
		};
	};*/
	if(ctrl->user_id < 4)
		((LightingScene*) scene)->setLightState(ctrl->user_id);
	else if(ctrl->user_id == 4)
		((LightingScene*) scene)->watchPause();
	else if(ctrl->user_id == 5)
		((LightingScene*) scene)->watchReset();
	
}

