#include "snes.h"

//extern Scene basicTestScene;
extern Scene Mode7TestScene;

extern Scene StartScreen;
extern Scene ExhibitView;
extern Scene DemoView;


Scene* timeline[] = {
	&StartScreen,
	&ExhibitView,
	&DemoView,
	//&basicTestScene,
    0
};
