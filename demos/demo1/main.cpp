#include <ModuleGame.hpp>
#include <OpenALInterface.hpp>
#include <SDLOpenGLInterface.hpp>
#include <PthreadsInterface.hpp>

int main(int argc, char* argv[])
{
	Module::ModuleGame game;
	
	Module::SDLOpenGLInterface graphics;
	Module::OpenALInterface audio;
	Module::PthreadsInterface threads;
	
	// Attatch the interfaces to the game
	game.attachThreadingInterface(&threads);
	game.attachGraphicsInterface(&graphics);
	game.attachAudioInterface(&audio);
	
	game.start();
	
	while (game.isRunning())
	{
		
	}
	
	return EXIT_SUCCESS;
}