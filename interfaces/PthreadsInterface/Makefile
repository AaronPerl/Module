PTHREAD_DIR = interfaces/PthreadsInterface
PTHREAD_SRCS = $(wildcard $(PTHREAD_DIR)/*.cpp)
PTHREAD_OBJS = $(PTHREAD_SRCS:.cpp=.o)

$(PTHREAD_DIR)/%.o : $(PTHREAD_DIR)/%.cpp $(PTHREAD_DIR)/*.hpp
	g++ $(FLAGS) $(LIB_INC_PATHS) -Iinclude -c $< -o $@

$(PTHREAD_DIR)/libPthreadsInterface.a : $(PTHREAD_OBJS)
	ar rcs $@ $^