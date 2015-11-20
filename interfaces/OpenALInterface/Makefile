OPENAL_DIR = interfaces/OpenALInterface
OPENAL_SRCS = $(wildcard $(OPENAL_DIR)/*.cpp)
OPENAL_OBJS = $(OPENAL_SRCS:.cpp=.o)

$(OPENAL_DIR)/%.o : $(OPENAL_DIR)/%.cpp $(OPENAL_DIR)/*.hpp
	g++ $(FLAGS) $(LIB_INC_PATHS) -Iinclude -c $< -o $@

$(OPENAL_DIR)/libOpenALInterface.a : $(OPENAL_OBJS)
	ar rcs $@ $^