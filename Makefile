GLM = lib/glm
SDL2 = lib/SDL2-2.0.3/x86_64-w64-mingw32
SDL2_32 = $(SDL2)/../i686-w64-mingw32
GLEW = lib/glew-1.11.0
BULLET = lib/bullet3

LIB_PATHS = -L$(GLEW)/lib -L$(SDL2)/lib -L$(BULLET)/lib
LIB_PATHS_32 = -L$(GLEW)/lib32 -L$(SDL2_32)/lib -L$(BULLET)/lib32
LIBS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglew32 -lBulletDynamics -lBulletCollision -lLinearMath
LIB_INC_PATHS = -I$(GLEW)/include -I$(SDL2)/include -I$(GLM) -I$(BULLET)/src
LIB_INC_PATHS_32 = -I$(GLEW)/include -I$(SDL2_32)/include -I$(GLM) -I$(BULLET)/src
FLAGS = -Wall -fstack-protector-all -fpic -Wstack-protector -D_FORTIFY_SOURCE=2

LIBRARY_NAME = Module
FULL_NAME = lib$(LIBRARY_NAME).a

INTERFACE_PATH = interfaces
INTERFACES = $(wildcard $(INTERFACE_PATH)/*)
INTERFACE_LIB_NAMES = $(addprefix lib, $(addsuffix .a, $(notdir $(INTERFACES))))
INTERFACE_LIBS = $(join $(addsuffix /, $(INTERFACES)), $(INTERFACE_LIB_NAMES))
INTERFACE_INC = $(addprefix -I,$(INTERFACES))
INTERFACE_LIB_PATHS = $(addprefix -L, $(INTERFACES))
INTERFACE_LINKS = $(addprefix -l, $(notdir $(INTERFACES)))

include $(addsuffix /Makefile, $(INTERFACES))


DEBUG ?= 1

ifeq ($(DEBUG), 1)
	#Debug mode
	FLAGS += -g -DDEBUG -ggdb3
	PATH64 = build/debug/64bit
	PATH32 = build/debug/32bit
else
	#Release mode
	FLAGS += -DNDEBUG
	ifeq ($(OS), Windows_NT)
		FLAGS += -mwindows
	endif
	PATH64 = build/release/64bit
	PATH32 = build/release/32bit
endif

DEP_PATH = depend
SRCS = $(wildcard src/*.cpp)
OBJS = $(notdir $(SRCS:.cpp=.o))
DEPS = $(notdir $(SRCS:.cpp=.d))
FULL_OBJS64 = $(addprefix $(PATH64)/,$(OBJS))
FULL_OBJS32 = $(addprefix $(PATH32)/,$(OBJS))
FULL_DEPS = $(addprefix $(DEP_PATH)/,$(DEPS))

ifeq ($(OS), Windows_NT)
	PATH64 := $(addsuffix /windows/mingw, $(PATH64))
	PATH32 := $(addsuffix /windows/mingw, $(PATH32))
else
	PATH64 := $(addsuffix /linux, $(PATH64))
	PATH32 := $(addsuffix /linux, $(PATH32))
endif

.PHONY: all
all: 64bit 32bit

.PHONY: depends
depends: $(FULL_DEPS)

.PHONY: 64bit
64bit: $(PATH64)/$(FULL_NAME)

.PHONY: 32bit
32bit: $(PATH32)/$(FULL_NAME)

.PHONY: test
test: 64bit
	g++ main_test.cpp -Iinclude -L$(PATH64) -l$(LIBRARY_NAME) $(INTERFACE_INC) $(LIB_PATHS) $(LIB_INC_PATHS) $(INTERFACE_LIB_PATHS) $(INTERFACE_LINKS) $(FLAGS) -lSDL2main -lSDL2 -lopengl32 -lglew32  -o main_test

.PHONY: clean
clean:
	rm -rf build
	
.PHONY: interfaces
interfaces: $(INTERFACE_LIBS)

$(PATH64):
	@echo Making 64-bit build directory
	@mkdir -p $(PATH64)
	
$(PATH32):
	@echo Making 32-bit build directory
	@mkdir -p $(PATH32)

$(DEP_PATH):
	@echo Making dependency directory
	@mkdir -p $(DEP_PATH)
	
$(PATH64)/%.o : src/%.cpp
	@echo Compiling $<
	@printf "  "
	g++ $< -c -Iinclude $(FLAGS) -o $@
	
$(PATH32)/%.o : src/%.cpp
	@echo Compiling $<
	@printf "  "
	i686-w64-mingw32-g++ $< -c -Iinclude $(FLAGS) -o $@
#$(DEP_PATH)/%.d : src/%.cpp
#	g++ -MF $@ -MG -MM -MP -MT $@ -MT $(<:.cpp=.o) $(FLAGS) $<

$(DEP_PATH)/%.d : src/%.cpp | $(DEP_PATH)
	@echo Generating dependencies for $<
	@g++ -MM -MT $(PATH64)/$(notdir $(<:.cpp=.o)) $(FLAGS) -Iinclude $< > $@
	@g++ -MM -MT $(PATH32)/$(notdir $(<:.cpp=.o)) $(FLAGS) -Iinclude $< >> $@

$(PATH64)/$(FULL_NAME): $(FULL_OBJS64)
	ar rcs $(PATH64)/$(FULL_NAME) $(PATH64)/*.o
#	g++ $(FLAGS) $(SRCS) $(LIB_PATHS) $(LIB_INC_PATHS) $(LIBS) -o $@
	
$(PATH32)/$(FULL_NAME): $(FULL_OBJS32)
	ar rcs $(PATH32)/$(FULL_NAME) $(PATH32)/*.o
#	i686-w64-mingw32-g++ $(FLAGS) $(SRCS) $(LIB_PATHS_32) $(LIB_INC_PATHS_32) $(LIBS) -o $@

$(FULL_OBJS64) : | $(PATH64)
$(FULL_OBJS32) : | $(PATH32)
$(FULL_DEPS) : | $(DEP_PATH)

-include $(FULL_DEPS)