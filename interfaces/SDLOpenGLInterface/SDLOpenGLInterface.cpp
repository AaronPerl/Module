#include "SDLOpenGLInterface.hpp"

Module::SDLOpenGLInterface::SDLOpenGLInterface() : 
	window(0), context(0), vShader(0), fShader(0), program(0), frames(0), prevMillis(0), running(false), terminated(false)
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_Init(SDL_INIT_EVERYTHING);
}

Module::SDLOpenGLInterface::~SDLOpenGLInterface()
{
	if (!terminated)
	{
		throw std::runtime_error("[GraphicsInterface] : SDLOpenGLInterface not properly destroyed!");
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
	std::cout << "[GraphicsInterface] : OpenGL :   Reading shader source file: " << path << std::endl;

	std::ifstream inputFile;
	inputFile.open(path);
	std::stringstream sStream;
	sStream << inputFile.rdbuf();
	std::string outString = sStream.str();

	std::cout << "[GraphicsInterface] : OpenGL :   Done reading shader source file: " << path<< std::endl;

	return outString;
}

unsigned int Module::SDLOpenGLInterface::initShader(const char * path, unsigned int shaderType)
{
	std::cout << "[GraphicsInterface] : OpenGL : Creating shader from file " << path << std::endl;

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
		throw std::runtime_error("[GraphcisInterface] : OpenGL :   Failed to compile shader: "+std::string(path));
	}

	std::cout << "[GraphicsInterface] : OpenGL :   Shader compiled : " << path << std::endl;

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
		throw std::runtime_error("[GraphicsInterface] : OpenGL : Failed to link shader program");
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
    // if (SDL_GL_SetSwapInterval(-1)==-1) // TODO change this to -1 for release
		// SDL_GL_SetSwapInterval(1);
    SDL_GL_SetSwapInterval(0);
    if (glewInit())
    {
    	throw std::runtime_error("[GraphicsInterface] : glew : Error initializing glew!");
    }
    
	glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_CULL_FACE);
	
	glGenBuffers(1, &batchModelVBO);
	glGenBuffers(1, &batchMVPVBO);
	glGenBuffers(1, &batchNormalVBO);
	
    setupShaders();
    SDL_GL_SwapWindow(window);
	prevMillis = getMilliseconds();
}

void Module::SDLOpenGLInterface::createVNBuffers(Mesh* mesh)
{
	GLuint vertexVBO;
	GLuint normalVBO;
	float* buffer;
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &normalVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
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
	
	// get locations of uniforms
	vloc = 	glGetUniformLocation(program, "view_matrix");
	// mloc = 	glGetUniformLocation(program, "model_matrix");
	prloc = 	glGetUniformLocation(program, "projection_matrix");
	// mvploc = glGetUniformLocation(program, "mvp_matrix");
	// nmloc = 	glGetUniformLocation(program, "norm_matrix");
	eploc = 	glGetUniformLocation(program, "eye_position");
	enloc = 	glGetUniformLocation(program, "eye_normal");
	
	vertexBuffers.push_back(vertexVBO);
	vertexBuffers.push_back(normalVBO);
}

Module::Mesh* Module::SDLOpenGLInterface::loadMeshFromFile(const std::string& meshname, const std::string& filename, bool flipFaces)
{
	std::cout << "[GraphicsInterface] Loading mesh [" << meshname << "] from file: " << filename << std::endl;
	std::size_t periodIndex = filename.rfind('.');
	if (periodIndex == std::string::npos)
	{
		std::cerr << "[GraphicsInterface]   File extension not found!" << std::endl;
		return NULL;
	}
	std::string extension = filename.substr(periodIndex);
	if (extension != ".obj")
	{
		std::cerr << "[GraphicsInterface]   Unsupported file format: " << extension << std::endl;
		return NULL;
	}
	std::cout << "[GraphicsInterface]   Recognized file type: " << extension << std::endl;
	
	std::ifstream modelFile(filename.c_str());
	
	if (!modelFile.is_open())
	{
		std::cerr << "[GraphicsInterface]   Invalid file name: " << filename << std::endl;
		return NULL;
	}
	
	std::string element;
	std::vector<Vector3> indexedVertices;
	std::vector<Vector3> indexedNormals;
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	
	while (!modelFile.eof())
	{
		int firstChar = modelFile.peek();
		if (firstChar == EOF)
			break;
		if (firstChar == '#')
		{
			modelFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			modelFile >> element;
			if (element == "v")
			{
				float x,y,z;
				modelFile >> x >> y >> z;
				indexedVertices.push_back(Vector3(x,y,z));
			} //endif v
			else if (element == "vn")
			{
				float x,y,z;
				modelFile >> x >> y >> z;
				indexedNormals.push_back(Vector3(x,y,z));
			} //endif vn
			else if (element == "f")
			{
				for (unsigned short i = 0; i < 3; i++)
				{
					std::string indexStr;
					modelFile >> indexStr;
					std::size_t slashIndex1 = indexStr.find('/');
					std::size_t slashIndex2 = std::string::npos;
					if (slashIndex1 != std::string::npos) // f v//n v//n v//n
					{
						slashIndex2 = indexStr.find('/', slashIndex1+1);
						if (slashIndex2 == std::string::npos)
						{
							std::cerr << "[GraphicsInterface]   Unsupported obj file" << std::endl;
							return NULL;
						}
						std::size_t slashIndex3 = indexStr.find('/', slashIndex2+1);
						if (slashIndex3 != std::string::npos)
						{
							std::cerr << "[GraphicsInterface]   Invalid file data" << std::endl;
							return NULL;
						}
						indexStr.replace(slashIndex1, slashIndex2 - slashIndex1 + 1, slashIndex2 - slashIndex1 + 1, ' ');
						std::size_t vi, ni;					
						std::stringstream indexStream(indexStr);
						indexStream >> vi >> ni;
						
						if (vi > indexedVertices.size() || ni > indexedNormals.size())
						{
							std::cerr << "[GraphicsInterface]   Unsupported/invalid obj file" << std::endl;
							return NULL;
						}
						vertices.push_back(indexedVertices[vi-1]);
						normals.push_back(indexedNormals[ni-1]);
					}
					else // f v v v
					{
						std::size_t vi;					
						std::stringstream indexStream(indexStr);
						indexStream >> vi;
						
						if (vi > indexedVertices.size() || vi > indexedNormals.size())
						{
							std::cerr << "[GraphicsInterface]   Unsupported/invalid obj file" << std::endl;
							return NULL;
						}
						
						vertices.push_back(indexedVertices[vi-1]);
						normals.push_back(indexedNormals[vi-1]);
					}
				} //endfor i from 0 to 3
				if (flipFaces)
				{
					Vector3 third  = vertices.back();
					vertices.pop_back();
					Vector3 second = vertices.back();
					vertices.pop_back();
					vertices.push_back(third);
					vertices.push_back(second);
					
					third  = normals.back();
					normals.pop_back();
					second = normals.back();
					normals.pop_back();
					normals.push_back(third);
					normals.push_back(second);
				}
			} // endif f
			modelFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	
	std::cout << "[GraphcisInterface]   Num vertices/normals: " << vertices.size() << " " << normals.size() << std::endl;
	
	std::cout << "[GraphicsInterface]   Successfully loaded file!" << std::endl;
	
	return createMesh(vertices, normals, meshname);
}

void Module::SDLOpenGLInterface::renderFrame()
{
	frames++;
	if (getMilliseconds() - prevMillis > 1000)
	{
		std::cout << "[GraphicsInterface] FPS: " << (frames/1.0f) << std::endl;
		prevMillis = getMilliseconds();
		frames = 0;
	}
	
	//	SDL stuff

	if (frames % 5 == 0)
	{
		SDL_Event event;
		SDL_PumpEvents();

		while (SDL_PollEvent(&event))
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
	Vector3 cameraPos(0,0,3);
	Vector3 lookVec(0,0,0);
	Vector3 upVec(0,1,0);
	if (camera != NULL)
	{
		Quaternion cameraRot = camera->getRotation();
		cameraPos = camera->getPosition();
		lookVec = Vector3(0,0,-1.0).rotate(cameraRot);
		upVec = Vector3(0,1.0,0).rotate(cameraRot);
	}
	Vector3 lookAt = cameraPos + lookVec;
	
	glm::mat4 viewMat = glm::lookAt(	glm::vec3(cameraPos.getX(),	cameraPos.getY(),	cameraPos.getZ()),
										glm::vec3(lookAt.getX(),	lookAt.getY(),		lookAt.getZ()	),
										glm::vec3(upVec.getX(),		upVec.getY(),		upVec.getZ())	);
	
	glUseProgram(program);
	
	// pass uniforms
	glUniformMatrix4fv(vloc,1,GL_FALSE,&viewMat[0][0]);
	glUniformMatrix4fv(prloc,1,GL_FALSE,&projectionMat[0][0]);
	glUniform4fv(eploc,1,&viewMat[3][0]);
	glUniform4fv(enloc,1,&viewMat[2][0]);
	
	// std::cout << "[GraphicsInterface] Enabling vertex attribute arrays" << std::endl;
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	for (unsigned int i = 0; i < 4; i++)
	{
			// Enable it
			glEnableVertexAttribArray(2 + i);
			glEnableVertexAttribArray(6 + i);
			glEnableVertexAttribArray(10 + i);
			// Make it instanced
			glVertexAttribDivisor(2 + i, 1);
			glVertexAttribDivisor(6 + i, 1);
			glVertexAttribDivisor(10 + i, 1);
	}
	
	// std::cout << "[GraphicsInterface] NumObjects = " << game->numObjects() << std::endl;
	// std::cout << "[GraphicsInterface] Drawing meshes" << std::endl;
		
	for (Book<Mesh>::size_type i = 0; i < allMeshes.size(); i++)
	{
		GLuint vertexVBO = 0;
		GLuint normalVBO = 0;
		Mesh* curMesh = &allMeshes[i];
		
		if (curMesh == NULL) // Nothing to see here, literally (no mesh)
			continue;
		
		vertexVBO = vertexBuffers[2 * curMesh->getIndex() + 0];
		normalVBO = vertexBuffers[2 * curMesh->getIndex() + 1];
		
		if (vertexVBO == 0 || normalVBO == 0) // This mesh is not in our book/invalid or the buffer for this mesh hasn't been generated yet
		{
			// std::cout << "[GraphicsInterface] No VBOs found" << std::endl;
			continue;
		}
		
		glm::mat4 meshScale = glm::scale(glm::mat4(1.0f),	glm::vec3(curMesh->getScale(), curMesh->getScale(), curMesh->getScale()));
		
		const std::vector<GameObject*>& instances = curMesh->getInstances();
		
		glm::mat4* modelMats 	= new glm::mat4[instances.size()];
		// glm::mat4* mvpMats 		= new glm::mat4[instances.size()];
		glm::mat4* normalMats 	= new glm::mat4[instances.size()];
		
		// std::cout << "[GraphicsInterface] Constructing model matrices" << std::endl;
		
		for (std::vector<GameObject*>::size_type j = 0; j < instances.size(); j++)
		{
			const Vector3& curPos = instances[j]->getPosition();
			const Quaternion& curRot = instances[j]->getRotation();
			// model matrix
			modelMats[j] = 	glm::translate(	glm::mat4(1.0f),	glm::vec3(curPos.getX(), curPos.getY(), curPos.getZ())	)*
							glm::toMat4(	glm::quat(curRot.getW(), curRot.getX(), curRot.getY(), curRot.getZ())		)*
							meshScale;
			
			// modelview projection matrix
			// mvpMats[j] = projectionMat * viewMat * modelMats[j];
			
			// normal matrix (inverse transpose of model matrix)
			normalMats[j] = glm::transpose(glm::inverse(modelMats[j]));
		}
				
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, batchModelVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instances.size(), modelMats, GL_STATIC_DRAW);
		
		for (int i = 0; i < 4; i++)
		{
			// Set up the vertex attribute
			glVertexAttribPointer(2 + i,              // Location
								  4, GL_FLOAT, GL_FALSE,       // vec4
								  sizeof(glm::mat4),                // Stride
								  (void *)(sizeof(glm::vec4) * i)); // Start offset
		}
		
		// glBindBuffer(GL_ARRAY_BUFFER, batchNormalVBO);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instances.size(), mvpMats, GL_STATIC_DRAW);
		
		// for (int i = 0; i < 4; i++)
		// {
			// // Set up the vertex attribute
			// glVertexAttribPointer(6 + i,              // Location
								  // 4, GL_FLOAT, GL_FALSE,       // vec4
								  // sizeof(glm::mat4),                // Stride
								  // (void *)(sizeof(glm::vec4) * i)); // Start offset
		// }
		
		glBindBuffer(GL_ARRAY_BUFFER, batchMVPVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instances.size(), normalMats, GL_STATIC_DRAW);
		
		for (int i = 0; i < 4; i++)
		{
			// Set up the vertex attribute
			glVertexAttribPointer(10 + i,              // Location
								  4, GL_FLOAT, GL_FALSE,       // vec4
								  sizeof(glm::mat4),                // Stride
								  (void *)(sizeof(glm::vec4) * i)); // Start offset
		}
		
		delete[] modelMats;
		// delete[] mvpMats;
		delete[] normalMats;
		
		// std::cout << "[GraphicsInterface] Drawing instances" << std::endl;
		
		glDrawArraysInstanced(GL_TRIANGLES, 0, curMesh->getNumVertices(), instances.size());
		
	}
	SDL_GL_SwapWindow(window);
}