#include "App.h"
int main( int argc, char** args )
{
	srand( SDL_GetTicks() );

	//GEngine engine;
	App engine;
	engine.set_caption("Initializing ... ");
	engine.init(800,600);
	engine.set_caption("Survival");
	engine.run();


	return 0;
}

