#include <ModuleGame.hpp>
#include <OpenALInterface.hpp>
#include <SDLOpenGLInterface.hpp>
#include <PthreadsInterface.hpp>
#include <Physics.hpp>

int main(int argc, char* argv[])
{
	Module::ModuleGame game;
	
	Module::SDLOpenGLInterface graphics;
	Module::OpenALInterface audio;
	Module::PthreadsInterface threads;
	
	Module::Physics physics(&game);
	
	game.addExtension(&physics);
	
	// Attatch the interfaces to the game
	game.attachThreadingInterface(&threads);
	game.attachGraphicsInterface(&graphics);
	game.attachAudioInterface(&audio);
	
	game.start();
	
	while (!game.isRunning());
	
	while (game.isRunning())
	{
		
	}
	
	return EXIT_SUCCESS;
}