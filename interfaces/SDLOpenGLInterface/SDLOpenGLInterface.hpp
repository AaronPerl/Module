#ifndef __SDLOPENGLINTERFACE_HPP__
#define __SDLOPENGLINTERFACE_HPP__

// C++ standard library includes
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <limits>

// Module includes
#include <ModuleGame.hpp>
#include <GraphicsInterface.hpp>
#include <Book.hpp>

// Library includes
#define GLM_FORCE_RADIANS
#define SDL_MAIN_HANDLED

#if defined(WIN32_) || defined(__CYGWIN__)
#include <windows.h>
#endif

#undef APIENTRY

#define GLEW_NO_GLU

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Module
{
	// A GraphicsInterface implementation that uses SDL2 for window creation and user input and OpenGL for rendering.
	class SDLOpenGLInterface : public GraphicsInterface
	{
		protected:
			Book<GLuint> vertexBuffers;
			Book<GLuint> vertexBuffers2D;
			
			SDL_Window *window;
			SDL_GLContext context;
			GLuint vShader;
			GLuint fShader;
			//GLuint gShader;
			GLuint program;
			GLuint vShader2D;
			GLuint fShader2D;
			GLuint program2D;
			GLuint frames;
			GLuint prevMillis;
			bool running;
			bool terminated;
			
			PolygonContainer* test;
	
			unsigned int initShader(const char * path, unsigned int shaderType);
			std::string readSource(const char * path);
			void setupShaders();
			void terminate();
	
			void createWindow(int width, int height, int fps);
			void createVNBuffers(Mesh* mesh);
			void createVertexBuffer(PolygonContainer* container);
			
			// OVERRIDES
			void createWindow() { createWindow(800, 600, 60); }
			void renderFrame();
			void drawPolygons2D(const PolygonContainer& container);
			void swapBuffers();
			unsigned long getMilliseconds() { return SDL_GetTicks(); }
			bool isRunning() { return running; }
			
		public:
			SDLOpenGLInterface();
			~SDLOpenGLInterface();
			
			Mesh* loadMeshFromFile(const std::string& meshname, const std::string& filename, bool flipFaces = false);
			
	};
}

#endif
