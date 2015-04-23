#include "SDLOpenGLInterface.hpp"

Module::SDLOpenGLInterface::SDLOpenGLInterface() : 
	window(0), context(0), vShader(0), fShader(0), program(0), running(false), terminated(false)
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_Init(SDL_INIT_EVERYTHING);
}

Module::SDLOpenGLInterface::~SDLOpenGLInterface()
{
	if (!terminated)
	{
		throw std::runtime_error("SDLOpenGLInterface not properly destroyed!");
	}
}

void Module::SDLOpenGLInterface::terminate()
{
	if (program)
	{
		glDeleteProgram(program);
	}
	if (window)
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	terminated = true;
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
	running = true;
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
	float* buffer;
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &normalVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	//glBufferStorage(GL_ARRAY_BUFFER, mesh->getNumVertices() * 3 * sizeof(float), NULL, GL_DYNAMIC_STORAGE_BIT);
	glBufferData(GL_ARRAY_BUFFER, mesh->getNumVertices() * 3 * sizeof(float), NULL, GL_STATIC_DRAW); // allocate buffer
	buffer = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (unsigned int i = 0; i < mesh->getNumVertices(); i++)
	{
		Vector3 curVec = mesh->getVertex(i);
		buffer[3*i+0] = curVec.getX();
		buffer[3*i+1] = curVec.getY();
		buffer[3*i+2] = curVec.getZ();
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	//glBufferStorage(GL_ARRAY_BUFFER, mesh->getNumVertices() * sizeof(float), NULL, GL_DYNAMIC_STORAGE_BIT);
	glBufferData(GL_ARRAY_BUFFER, mesh->getNumVertices() * 3 * sizeof(float), NULL, GL_STATIC_DRAW); // allocate buffer
	buffer = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (unsigned int i = 0; i < mesh->getNumVertices(); i++)
	{
		Vector3 curVec = mesh->getNormal(i);
		buffer[3*i+0] = curVec.getX();
		buffer[3*i+1] = curVec.getY();
		buffer[3*i+2] = curVec.getZ();
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	vertexBuffers.push_back(vertexVBO);
	vertexBuffers.push_back(normalVBO);
	
	std::cout << "Made vertex/normal buffers!" << std::endl;
}

void Module::SDLOpenGLInterface::renderFrame()
{
	
	// SDL stuff

	SDL_Event event;
	SDL_PumpEvents();

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				std::cout << "SDL Program closed!" << std::endl;
				terminate();
				running = false;
				break;
		}
	}
	
	int width;
	int height;
	
	SDL_GetWindowSize(window,&width,&height);
	
	// create new VBOs
	
	while (allMeshes.size() > vertexBuffers.size()) // make sure any new meshes have buffer objects
	{
		createVNBuffers(&allMeshes[vertexBuffers.size()]);
	}
	
	// OpenGL stuff now
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	// projection matrix
	glm::mat4 projectionMat = glm::perspective(1.0472f, width/(float)height, 0.1f, 100.0f);
	
	// view matrix
	glm::mat4 viewMat = glm::lookAt(	glm::vec3(0,0,3),
										glm::vec3(0,0,0),
										glm::vec3(0,1,0));
										
	// model matrix
	glm::mat4 modelMat;
	
	glUseProgram(program);
	
	// get locations of uniforms
	GLuint vloc = 	glGetUniformLocation(program, "view_matrix");
	GLuint mloc = 	glGetUniformLocation(program, "model_matrix");
	GLuint prloc = 	glGetUniformLocation(program, "projection_matrix");
	GLuint mvploc = glGetUniformLocation(program, "mvp_matrix");
	GLuint nmloc = 	glGetUniformLocation(program, "norm_matrix");
	GLuint eploc = 	glGetUniformLocation(program, "eye_position");
	GLuint enloc = 	glGetUniformLocation(program, "eye_normal");
	
	// pass uniforms
	glUniformMatrix4fv(vloc,1,GL_FALSE,&viewMat[0][0]);
	glUniformMatrix4fv(prloc,1,GL_FALSE,&projectionMat[0][0]);
	glUniform4fv(eploc,1,&viewMat[3][0]);
	glUniform4fv(enloc,1,&viewMat[2][0]);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	for (Book<GameObject>::size_type i = 0; i < game->numObjects(); i++)
	{
		std::cout << "GameObject: " << i << std::endl;
		GLuint vertexVBO = 0;
		GLuint normalVBO = 0;
		GameObject* curObj = game->getGameObject(i);
		Mesh* curMesh = curObj->getMesh();
		Vector3 curPos = curObj->getPosition();
		Quaternion curRot = curObj->getRotation();
		std::cout << "  hasMesh: " << curMesh << std::endl;
		if (curMesh == NULL) // Nothing to see here, literally (no mesh)
			continue;
		for (Book<Mesh>::size_type j = 0; j < allMeshes.size(); j++) // find the index of this mesh, TODO make better
		{
			if (&allMeshes[j] == curMesh)
			{
				vertexVBO = vertexBuffers[2*j+0];
				normalVBO = vertexBuffers[2*j+1];
				break;
			}
		}
		if (vertexVBO == 0 || normalVBO == 0) // This mesh is not in our book/invalid or the buffer for this mesh hasn't been generated yet
			continue;
		
		std::cout << "  vertexVBO: " << vertexVBO << "  normalVBO: " << normalVBO << std::endl;
		
		modelMat = 	glm::translate(	glm::mat4(1.0f),	glm::vec3(curPos.getX(), curPos.getY(), curPos.getZ())	)*
					glm::toMat4(	glm::quat(curRot.getW(), curRot.getX(), curRot.getY(), curRot.getZ())		)*
					glm::scale(		glm::mat4(1.0f),	glm::vec3(1.0,1.0,1.0)									);
		
		// modelview projection matrix
		glm::mat4 mvp = projectionMat * viewMat * modelMat;
		// normal matrix (inverse transpose of model matrix)
		glm::mat4 normMat = glm::transpose(glm::inverse(modelMat));
		
		glUniformMatrix4fv(mloc,1,GL_FALSE,&modelMat[0][0]);
		glUniformMatrix4fv(mvploc,1,GL_FALSE,&mvp[0][0]);
		glUniformMatrix4fv(nmloc,1,GL_FALSE,&normMat[0][0]);
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, curMesh->getNumVertices());
		
		SDL_GL_SwapWindow(window);
	}
}