#include "SDLOpenGLInterface.hpp"

Module::SDLOpenGLInterface::SDLOpenGLInterface() : 
	window(0), context(0), vShader(0), fShader(0), program(0)
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_Init(SDL_INIT_EVERYTHING);
}

Module::SDLOpenGLInterface::~SDLOpenGLInterface()
{
	glDeleteProgram(program);
	SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::string Module::SDLOpenGLInterface::readSource(const char * path)
{
	std::cout << "Reading shader source file: " << path << std::endl;

	std::ifstream inputFile;
	inputFile.open(path);
	std::stringstream sStream;
	sStream << inputFile.rdbuf();
	std::string outString = sStream.str();

	std::cout << "Done reading shader source file: " << path<< std::endl;

	return outString;
}

unsigned int Module::SDLOpenGLInterface::initShader(const char * path, unsigned int shaderType)
{
	std::cout << "Creating shader from file " << path << std::endl;

	std::string sourceString = readSource(path);
	unsigned int newShader = glCreateShader(shaderType);
	std::cout.flush();

	int sourceLength = sourceString.length();
	const char * sourceCString = sourceString.c_str();
	glShaderSource(newShader,1,&sourceCString,&sourceLength);
	glCompileShader(newShader);

	GLint compiled;
	glGetShaderiv(newShader,GL_COMPILE_STATUS,&compiled);

	if (compiled==GL_FALSE)
	{
		GLint logLen = 0;
		glGetShaderiv(newShader, GL_INFO_LOG_LENGTH, &logLen);
		char * log = new char[logLen];
		glGetShaderInfoLog(newShader,logLen,NULL,log);
		std::ofstream logFile ("logs/shaderLog.txt");
		logFile << log << std::endl;
		logFile.close ();
		delete log;
		std::cout.flush();
		throw std::runtime_error("Failed to compile shader: "+std::string(path));
	}

	std::cout << "Shader compiled : " << path << std::endl;

	return newShader;
}

void Module::SDLOpenGLInterface::setupShaders()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
	
	vShader = initShader("shaders/vs.glsl",GL_VERTEX_SHADER);
	fShader = initShader("shaders/fs.glsl",GL_FRAGMENT_SHADER);
	
	program = glCreateProgram();
	glAttachShader(program,vShader);
	glAttachShader(program,fShader);
	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program,GL_LINK_STATUS,&linked);

	if (linked==GL_FALSE)
	{
		GLint logLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
		char * log = new char[logLen];
		glGetProgramInfoLog(program,logLen,NULL,log);
		std::ofstream logFile ("logs/programLog.txt");
		logFile << log << std::endl;
		logFile.close ();
		delete log;
		std::cout.flush();
		throw std::runtime_error("Failed to link program");
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void Module::SDLOpenGLInterface::createWindow(int width, int height, int fps)
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	window = SDL_CreateWindow("SDL Program",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
    if (SDL_GL_SetSwapInterval(-1)==-1) // TODO change this to -1 for release
    	SDL_GL_SetSwapInterval(1);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    if (glewInit())
    {
    	throw std::runtime_error("Error initializing glew!");
    }
    setupShaders();
    SDL_GL_SwapWindow(window);
}

void Module::SDLOpenGLInterface::createVNBuffers(Mesh* mesh)
{
	GLuint vertexVBO;
	GLuint normalVBO;
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &normalVBO);
	
}

void Module::SDLOpenGLInterface::renderFrame()
{
	while (allMeshes.size() > vertexBuffers.size()) // make sure any new meshes have buffer objects
	{
		createVNBuffers(&allMeshes[vertexBuffers.size()]);
	}
	
	
}