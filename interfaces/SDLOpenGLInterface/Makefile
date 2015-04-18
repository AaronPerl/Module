SDLOPENGL_DIR = interfaces/SDLOpenGLInterface
SDLOPENGL_SRCS = $(wildcard $(SDLOPENGL_DIR)/*.cpp)
SDLOPENGL_OBJS = $(SDLOPENGL_SRCS:.cpp=.o)

$(SDLOPENGL_DIR)/%.o : $(SDLOPENGL_DIR)/%.cpp $(SDLOPENGL_DIR)/*.hpp
	g++ $(FLAGS) $(LIB_INC_PATHS) -Iinclude -c $< -o $@

$(SDLOPENGL_DIR)/libSDLOpenGLInterface.a : $(SDLOPENGL_OBJS)
	ar rcs $@ $(SDLOPENGL_OBJS)