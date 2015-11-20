#include "SDLOpenGLInterface.hpp"
#include "SDLKeyCodes.hpp"
#include "PolygonContainer.hpp"

using namespace Module;

SDLOpenGLInterface::SDLOpenGLInterface() : 
	window(0), context(0), vShader(0), fShader(0), program(0), frames(0), prevMillis(0), running(false), terminated(false)
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_Init(SDL_INIT_EVERYTHING);
}

SDLOpenGLInterface::~SDLOpenGLInterface()
{
	if (!terminated)
	{
		throw std::runtime_error("[GraphicsInterface] : SDLOpenGLInterface not properly destroyed!");
	}
}

void SDLOpenGLInterface::terminate()
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

std::string SDLOpenGLInterface::readSource(const char * path)
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

unsigned int SDLOpenGLInterface::initShader(const char * path, unsigned int shaderType)
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

void SDLOpenGLInterface::setupShaders()
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
		glGetProgramInfoLog(program2D,logLen,NULL,log);
		std::ofstream logFile ("logs/programLog.txt");
		logFile << log << std::endl;
		logFile.close ();
		delete log;
		std::cout.flush();
		throw std::runtime_error("[GraphicsInterface] : OpenGL : Failed to link shader program");
	}
	
	vShader2D = initShader("shaders/vs2D.glsl",GL_VERTEX_SHADER);
	fShader2D = initShader("shaders/fs2D.glsl",GL_FRAGMENT_SHADER);
	
	program2D = glCreateProgram();
	glAttachShader(program2D,vShader2D);
	glAttachShader(program2D,fShader2D);
	glLinkProgram(program2D);
	glGetProgramiv(program2D,GL_LINK_STATUS,&linked);

	if (linked==GL_FALSE)
	{
		GLint logLen = 0;
		glGetProgramiv(program2D, GL_INFO_LOG_LENGTH, &logLen);
		char * log = new char[logLen];
		glGetProgramInfoLog(program2D,logLen,NULL,log);
		std::ofstream logFile ("logs/programLog.txt");
		logFile << log << std::endl;
		logFile.close ();
		delete log;
		std::cout.flush();
		throw std::runtime_error("[GraphicsInterface] : OpenGL : Failed to link 2D shader program");
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteShader(vShader2D);
	glDeleteShader(fShader2D);
}

void SDLOpenGLInterface::createWindow(int width, int height, int fps)
{
	running = true;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	window = SDL_CreateWindow("SDL Program",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
    // if (SDL_GL_SetSwapInterval(-1)==-1) // TODO change this to -1 for release
		// SDL_GL_SetSwapInterval(1);
    SDL_GL_SetSwapInterval(0);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_CULL_FACE);
    if (glewInit())
    {
    	throw std::runtime_error("[GraphicsInterface] : glew : Error initializing glew!");
    }
	if (!GLEW_VERSION_3_1)
	{
		throw std::runtime_error("[GraphicsInterface] : OpenGL : Version 3.1 not supported!");
	}
    setupShaders();
    SDL_GL_SwapWindow(window);
	prevMillis = getMilliseconds();
}

void SDLOpenGLInterface::createVNBuffers(Mesh* mesh)
{
	GLuint vertexVBO  = 0;
	GLuint normalVBO  = 0;
	GLuint textureVBO = 0;
	float* buffer;
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &normalVBO);
	glGenBuffers(1, &textureVBO);
	
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
	
	
	if (mesh->hasUVs())
	{
		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		//glBufferStorage(GL_ARRAY_BUFFER, mesh->getNumVertices() * sizeof(float), NULL, GL_DYNAMIC_STORAGE_BIT);
		glBufferData(GL_ARRAY_BUFFER, mesh->getNumVertices() * 2 * sizeof(float), NULL, GL_STATIC_DRAW); // allocate buffer
		buffer = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		for (unsigned int i = 0; i < mesh->getNumVertices(); i++)
		{
			std::pair<float,float> curUV = mesh->getUV(i);
			buffer[2*i+0] = curUV.first;
			buffer[2*i+1] = curUV.second;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	vertexBuffers.push_back(vertexVBO);
	vertexBuffers.push_back(normalVBO);
	vertexBuffers.push_back(textureVBO);
}

void SDLOpenGLInterface::createVertexBuffer(PolygonContainer* container)
{
	GLuint vertexVBO;
	float* buffer;
	const float* vertices = container->getCoordinates().data();
	glGenBuffers(1, &vertexVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, container->numVertices() * 3 * sizeof(float), NULL, GL_STATIC_DRAW);
	buffer = (float*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	for (unsigned int i = 0; i < container->numVertices() * 3; i++)
	{
		buffer[i] = vertices[i];
		std::cout << "coordinate i:" << vertices[i] << std::endl;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	vertexBuffers2D.push_back(vertexVBO);
}

std::vector<std::string> split(const std::string& toSplit)
{
	std::vector<std::string> retval;
	int curPos = toSplit.find_first_not_of(" ", 0);
	while (curPos != std::string::npos)
	{
		int nextPos = toSplit.find_first_of(" ", curPos);
		retval.push_back(toSplit.substr(curPos, nextPos - curPos));
		curPos = toSplit.find_first_not_of(" ", nextPos);
	}
	return retval;
}

Mesh* SDLOpenGLInterface::loadMeshFromFile(const std::string& meshname, const std::string& filename, bool flipFaces)
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
	std::vector<float> indexedUVs;
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<float> uvs;
	
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
			else if (element == "vt")
			{
				float u,v;
				modelFile >> u >> v;
				indexedUVs.push_back(u);
				indexedUVs.push_back(v);
			}
			else if (element == "f")
			{
				char curLine[256];
				modelFile.getline(curLine, 256);
				if (modelFile.fail())
				{
					std::cerr << "[GraphicsInterface]   File line too long" << std::endl;
					return NULL;
				}
				unsigned int numVertices = 0;
				std::vector<std::string> tokens = split(curLine);
				if (tokens.size() < 3)
				{
					std::cerr << "[GraphicsInterface]   Not enough vertices in face!" << std::endl;
					return NULL;
				}
				for (unsigned short i = 0; i < tokens.size(); i++)
				{
					std::string indexStr = tokens[i];
					std::size_t slashIndex1 = indexStr.find('/');
					std::size_t slashIndex2 = std::string::npos;
					if (slashIndex1 != std::string::npos) // f v//n v//n v//n or f v/t/n v/t/n v/t/n
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
						indexStr[slashIndex1] = ' ';
						indexStr[slashIndex2] = ' ';
						// indexStr.replace(slashIndex1, slashIndex2 - slashIndex1 + 1, slashIndex2 - slashIndex1 + 1, ' ');
						std::size_t vi, ti, ni;
						bool has_ti;
						std::stringstream indexStream(indexStr);
						if (slashIndex2 == slashIndex1 + 1)
						{
							indexStream >> vi >> ni;
							ti = 0;
							has_ti = false;
						}
						else
						{
							indexStream >> vi >> ti >> ni;
							has_ti = true;
						}
						
						if (vi > indexedVertices.size() || ni > indexedNormals.size() || ti * 2 > indexedUVs.size())
						{
							std::cerr << "[GraphicsInterface]   Unsupported/invalid obj file" << std::endl;
							return NULL;
						}
						if (i < 3)
						{
							vertices.push_back(indexedVertices[vi-1]);
							normals.push_back(indexedNormals[ni-1]);
							if (has_ti)
							{
								uvs.push_back(indexedUVs[ti * 2 - 2]);
								uvs.push_back(indexedUVs[ti * 2 - 1]);
							}
							else
							{
								uvs.push_back(0.0f);
								uvs.push_back(0.0f);
							}
						}
						else
						{
							unsigned int firstIndex = vertices.size() - i;
							unsigned int lastIndex = vertices.size() - 1;
							vertices.push_back(vertices[firstIndex]);
							vertices.push_back(vertices[lastIndex]);
							vertices.push_back(indexedVertices[vi-1]);
							normals.push_back(normals[firstIndex]);
							normals.push_back(normals[lastIndex]);
							normals.push_back(indexedNormals[ni-1]);
							if (has_ti)
							{
								uvs.push_back(uvs[firstIndex * 2]);
								uvs.push_back(uvs[firstIndex * 2 + 1]);
								
								uvs.push_back(uvs[lastIndex * 2]);
								uvs.push_back(uvs[lastIndex * 2 + 1]);
								
								uvs.push_back(indexedUVs[ti * 2 - 2]);
								uvs.push_back(indexedUVs[ti * 2 - 1]);
							}
							else
							{
								uvs.push_back(0.0f);
								uvs.push_back(0.0f);
								
								uvs.push_back(0.0f);
								uvs.push_back(0.0f);
								
								uvs.push_back(0.0f);
								uvs.push_back(0.0f);
							}
						}
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
				} //endfor i from 0 to tokens.size
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
			if (element != "f")
				modelFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	
	std::cout << "[GraphcisInterface]   Num vertices/normals: " << vertices.size() << " " << normals.size() << std::endl;
	
	std::cout << "[GraphicsInterface]   Successfully loaded file!" << std::endl;
	
	return createMesh(vertices, normals, uvs, meshname);
}

Texture* SDLOpenGLInterface::loadTexture(const std::string& filename)
{
	textures.push_back(SDLOpenGLTexture());
	texturesToLoad.push_back(&textures.back());
	filesToLoadFrom.push_back(filename);
	return &textures.back();
}

void SDLOpenGLInterface::loadNewTextures()
{
	for (unsigned int i = 0; i < texturesToLoad.size(); i++)
	{
		SDLOpenGLTexture* curTex = texturesToLoad[i];
		const std::string& curFilename = filesToLoadFrom[i];
		GLuint newID = SOIL_load_OGL_texture
		(
			curFilename.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB
			//SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		if (newID == 0)
			throw std::runtime_error("[GraphicsInterface] : Texture " + curFilename + " could not be loaded");
		curTex->textureID = newID;
	}
	texturesToLoad.clear();
	filesToLoadFrom.clear();
}

void SDLOpenGLInterface::renderFrame()
{
	frames++;
	if (getMilliseconds() - prevMillis > 5000)
	{
		std::cout << "[GraphicsInterface] FPS: " << (frames/5.0f) << std::endl;
		prevMillis = getMilliseconds();
		frames = 0;
	}
	
	//	SDL stuff

	SDL_Event event;
	SDL_PumpEvents();

	while (SDL_PollEvent(&event))
	{
		uint8_t mouseButton = 255;
		switch (event.type)
		{
			case SDL_QUIT:
				std::cout << "SDL Program closed!" << std::endl;
				terminate();
				running = false;
				return;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						mouseButton = 0;
						break;
					case SDL_BUTTON_MIDDLE:
						mouseButton = 2;
						break;
					case SDL_BUTTON_RIGHT:
						mouseButton = 1;
						break;
				}
				if (mouseButton != 255)
					mousePressed(	mouseButton,
									(uint16_t) event.button.x,
									(uint16_t) event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						mouseButton = 0;
						break;
					case SDL_BUTTON_MIDDLE:
						mouseButton = 2;
						break;
					case SDL_BUTTON_RIGHT:
						mouseButton = 1;
						break;
				}
				if (mouseButton != 255)
					mouseReleased(	mouseButton,
									(uint16_t) event.button.x,
									(uint16_t) event.button.y);
				break;
			case SDL_MOUSEMOTION:
				mouseMoved(	(uint16_t) event.motion.x,
							(uint16_t) event.motion.y,
							(int16_t) event.motion.xrel,
							(int16_t) event.motion.yrel);
				break;
			case SDL_KEYDOWN:
				if (!event.key.repeat)
				{
					SDL_Keycode key = event.key.keysym.sym;
					uint16_t mod = event.key.keysym.mod;
					keyPressed(getKeyCode(key), getChar(key,mod));
				}
				break;
			case SDL_KEYUP:
				SDL_Keycode key = event.key.keysym.sym;
				uint16_t mod = event.key.keysym.mod;
				keyReleased(getKeyCode(key), getChar(key,mod));
				break;
		}
	}
	
	int width;
	int height;
	
	SDL_GetWindowSize(window,&width,&height);
	
	if (width == 0 || height == 0)
		return;
	
	glViewport(0,0,width,height);
    glDepthFunc(GL_LESS);
	
	// create new VBOs
	
	while (allMeshes.size() * 2 > vertexBuffers.size()) // make sure any new meshes have buffer objects
	{
		createVNBuffers(&allMeshes[vertexBuffers.size()/2]);
	}
	
	if (texturesToLoad.size() > 0)
		loadNewTextures();
	// OpenGL stuff now
		
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
	GLuint texloc = glGetUniformLocation(program, "texture");
	
	glm::vec3 eyePos(cameraPos.getX(), cameraPos.getY(), cameraPos.getZ());
	glm::vec3 eyeNorm(lookAt.getX(), lookAt.getY(), lookAt.getZ());
	
	// pass uniforms
	glUniformMatrix4fv(vloc,1,GL_FALSE,&viewMat[0][0]);
	glUniformMatrix4fv(prloc,1,GL_FALSE,&projectionMat[0][0]);
	
	glUniform3fv(eploc,1,&eyePos[0]);
	glUniform3fv(enloc,1,&eyeNorm[0]);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	// std::cout << "[GraphicsInterface] NumObjects = " << game->numObjects() << std::endl;
		
	for (Book<GameObject>::size_type i = 0; i < game->numObjects(); i++)
	{
		GLuint vertexVBO = 0;
		GLuint normalVBO = 0;
		GLuint textureVBO = 0;
		GameObject* curObj = game->getGameObject(i);
		Mesh* curMesh = curObj->getMesh();
		Texture* curTex = curObj->getTexture();
		SDLOpenGLTexture* curSDLOGLTex;
		Vector3 curPos = curObj->getPosition();
		Quaternion curRot = curObj->getRotation();
		if (curMesh == NULL) // Nothing to see here, literally (no mesh)
		{
			// std::cout << "[GraphicsInterface] No mesh, skipping GameObject" << std::endl;
			continue;
		}
		if (curTex != NULL && (curSDLOGLTex = (dynamic_cast<SDLOpenGLTexture*>(curTex))) != NULL && curSDLOGLTex->textureID != 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, curSDLOGLTex->textureID);
			glUniform1i(texloc, GL_TEXTURE0);
		}
		
		vertexVBO = vertexBuffers[3 * curMesh->getIndex() + 0];
		normalVBO = vertexBuffers[3 * curMesh->getIndex() + 1];
		textureVBO = vertexBuffers[3 * curMesh->getIndex() + 2];
		
		if (vertexVBO == 0 || normalVBO == 0 || textureVBO == 0) // This mesh is not in our book/invalid or the buffer for this mesh hasn't been generated yet
		{
			// std::cout << "[GraphicsInterface] No VBOs found" << std::endl;
			continue;
		}
		
		modelMat = 	glm::translate(	glm::mat4(1.0f),	glm::vec3(curPos.getX(), curPos.getY(), curPos.getZ())					)*
					glm::toMat4(	glm::quat(curRot.getW(), curRot.getX(), curRot.getY(), curRot.getZ())						)*
					glm::scale(		glm::mat4(1.0f),	glm::vec3(curMesh->getScale(),curMesh->getScale(),curMesh->getScale())	);
		
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
		
		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, curMesh->getNumVertices());
		
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

void SDLOpenGLInterface::drawPolygons2D(const PolygonContainer& container)
{
	glUseProgram(program2D);
	
	GLint dimensions[2];
	SDL_GetWindowSize(window,&dimensions[0],&dimensions[1]);
	
	glDisable(GL_CULL_FACE);
	glDepthFunc(GL_ALWAYS);
	
	// create new VBOs
	
	while (allPolygons.size() > vertexBuffers2D.size()) // make sure any new meshes have buffer objects
	{
		createVertexBuffer(&allPolygons[vertexBuffers2D.size()]);
	}
	
	GLuint vertexVBO = vertexBuffers2D[container.getIndex()];
	GLuint dimensionLoc = glGetUniformLocation(program2D, "position");
	
	glUniform2iv(dimensionLoc,1,dimensions);
	
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(GL_TRIANGLES, 0, container.numVertices());
	
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	
	glEnable(GL_CULL_FACE);
}

void SDLOpenGLInterface::swapBuffers()
{
	SDL_GL_SwapWindow(window);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

KeyCode::Code Module::getKeyCode(SDL_Keycode sym)
{
	if (sym < 0x40000000)
	{
		return lowLookup[sym];
	}
	else
	{
		return highLookup[sym & ~0x40000000];
	}
}

uint8_t Module::getChar(SDL_Keycode sym, uint16_t mod)
{
	if ((sym & 0x40000000) != 0x40000000)
	{
		if (mod & KMOD_SHIFT)
		{
			if (sym >= 'a' && sym <= 'z')
			{
				return sym - 'a' + 'A';
			}
			else
			{
				switch (sym)
				{
				case '1':
					return '!';
				case '2':
					return '@';
				case '3':
					return '#';
				case '4':
					return '$';
				case '5':
					return '%';
				case '6':
					return '^';
				case '7':
					return '&';
				case '8':
					return '*';
				case '9':
					return '(';
				case '0':
					return ')';
				case '-':
					return '_';
				case '=':
					return '+';
				case '`':
					return '~';
				case '\\':
					return '|';
				case '[':
					return '{';
				case ']':
					return '}';
				case ';':
					return ':';
				case '\'':
					return '"';
				case ',':
					return '<';
				case '.':
					return '>';
				case '/':
					return '?';
				}
			}
		}
		else
		{
			return (wchar_t) sym;
		}	
	}
		return '\000';
}