GLM = lib/glm
SDL2 = lib/SDL2-2.0.3/x86_64-w64-mingw32
SDL2_32 = $(SDL2)/../i686-w64-mingw32
GLEW = lib/glew-1.11.0
BULLET = lib/bullet3
OPENAL_SOFT = lib/openal-soft-1.16.0
FREEALUT = lib/freealut
SOIL = lib/SOIL

#LIBS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglew32 -lBulletDynamics -lBulletCollision -lLinearMath
LIBS 			:= -lalut -lSDL2main -lSDL2 -lSOIL
LIB_INC_PATHS 		:= -I$(GLEW)/include -I$(SDL2)/include -I$(GLM) -I$(BULLET)/src -I$(OPENAL_SOFT)/include -I$(FREEALUT)/include -I$(SOIL)/src
LIB_INC_PATHS_32 	:= -I$(GLEW)/include -I$(SDL2_32)/include -I$(GLM) -I$(BULLET)/src -I$(OPENAL_SOFT)/include -I$(FREEALUT)/include -I$(SOIL)/src
LIB_PATHS		:= -L$(FREEALUT)/lib
LIB_PATHS32		:=


DUMPNAME = $(shell gcc -dumpmachine)

IS_CYGWIN = false
NEEDS_PTHREADS_WIN32 = false

ifeq ($(OS), Windows_NT)
	NEEDS_PTHREADS_WIN32 = true
else
	LIBS += -lopenal
endif

ifeq ($(DUMPNAME), x86_64-pc-cygwin)
	NEEDS_PTHREADS_WIN32 = false
	IS_CYGWIN = true
endif

ifeq ($(DUMPNAME), i686-pc-cygwin)
	NEEDS_PTHREADS_WIN32 = false
	IS_CYGWIN = true
endif

LIBRARY_NAME = Module
FULL_NAME = lib$(LIBRARY_NAME).a
FLAGS = -Wall -fstack-protector-all -fpic -Wstack-protector -D_FORTIFY_SOURCE=2

INTERFACE_PATH = interfaces
INTERFACE_PATHS = $(wildcard $(INTERFACE_PATH)/*)
INTERFACE_FILE_NAMES = $(addprefix lib, $(addsuffix .a, $(notdir $(INTERFACE_PATHS))))
INTERFACE_LIBS = $(join $(addsuffix /, $(INTERFACE_PATHS)), $(INTERFACE_FILE_NAMES))
INTERFACE_INC = $(addprefix -I,$(INTERFACE_PATHS))
INTERFACE_LIB_PATHS = $(addprefix -L, $(INTERFACE_PATHS))
INTERFACE_LINKS = $(addprefix -l, $(notdir $(INTERFACE_PATHS)))


include $(addsuffix /Makefile, $(INTERFACE_PATHS))


DEBUG ?= 1

ifeq ($(DEBUG), 1)
	#Debug mode
	FLAGS += -g -DDEBUG -ggdb3
	PATH64 := build/debug/64bit
	PATH32 := build/debug/32bit
else
	#Release mode
	FLAGS += -DNDEBUG
	ifeq ($(OS), Windows_NT)
		FLAGS += -mwindows
	endif
	PATH64 := build/release/64bit
	PATH32 := build/release/32bit
endif

DEP_PATH = depend
SRCS = $(wildcard src/*.cpp)
OBJS = $(notdir $(SRCS:.cpp=.o))
DEPS = $(notdir $(SRCS:.cpp=.d))
FULL_OBJS64 = $(addprefix $(PATH64)/,$(OBJS))
FULL_OBJS32 = $(addprefix $(PATH32)/,$(OBJS))
FULL_DEPS = $(addprefix $(DEP_PATH)/,$(DEPS))
NULL = 

ifeq ($(OS), Windows_NT)
	LIB_PATHS 		+= -L$(GLEW)/lib -L$(SDL2)/lib -L$(BULLET)/lib -L$(OPENAL_SOFT)/libs/Win64 -L$(SOIL)/lib
	LIB_PATHS_32 	+= -L$(GLEW)/lib32 -L$(SDL2_32)/lib -L$(BULLET)/lib32 -L$(OPENAL_SOFT)/libs/Win32 -L$(SOIL)/lib
	LIBS		+= -lopengl32 -lglew32 -lOpenAL32.dll
	ifeq ($(IS_CYGWIN), false)
		LIBS   :=  -lmingw32 $(LIBS)
		PATH64 := $(addsuffix /windows/mingw-w64, $(PATH64))
		PATH32 := $(addsuffix /windows/mingw-w64, $(PATH32))
	else
		PATH64 := $(addsuffix /windows/cygwin, $(PATH64))
		PATH32 := $(addsuffix /windows/cygwin, $(PATH32))
	endif
	NULL := nul
else
	LIBS		+= -lGL -lGLEW
	PATH64 := $(addsuffix /linux, $(PATH64))
	PATH32 := $(addsuffix /linux, $(PATH32))
	NULL := /dev/null
endif

ifeq ($(NEEDS_PTHREADS_WIN32), true)
	PTHREADS = lib/pthreads-win32
	LIB_PATHS += -L$(PTHREADS)/lib/x64
	LIB_PATHS_32 += -L$(PTHREADS)/lib/x32
	LIBS += -lpthreadGC2
	LIB_INC_PATHS += -I$(PTHREADS)/include
	LIB_INC_PATHS32 += -I$(PTHREADS)/include
else
	LIBS += -lpthread
endif

.DEFAULT_GOAL = 64bit

.PHONY: all depends 64bit 32bit interfaces test run clean dumpmachine

all: 64bit 32bit
depends: $(FULL_DEPS)
64bit: $(PATH64)/$(FULL_NAME)
32bit: $(PATH32)/$(FULL_NAME)
interfaces: $(INTERFACE_LIBS)
test: 64bit interfaces
	@echo Compiling test program!
	@g++ main_test.cpp -Iinclude -L$(PATH64) -l$(LIBRARY_NAME) $(INTERFACE_INC) $(LIB_PATHS) $(LIB_INC_PATHS) $(INTERFACE_LIB_PATHS) $(INTERFACE_LINKS) $(LIBS) $(FLAGS) -o main_test
run: test
	main_test
clean:
	@echo Files are: $(foreach dir, $(INTERFACE_PATHS), $(wildcard $(dir)/*.o))
	rm -rf build $(DEP_PATH) $(INTERFACE_LIBS) $(foreach dir, $(INTERFACE_PATHS), $(wildcard $(dir)/*.o))
dumpmachine:
	echo

$(PATH64):
	@echo Making 64-bit build directory
	@mkdir $(PATH64) -p 2>$(NULL) || mkdir $(subst /,\,$(PATH64))

$(PATH32):
	@echo Making 32-bit build directory
	@mkdir $(PATH32) -p 2>$(NULL) || mkdir $(subst /,\,$(PATH32))

$(DEP_PATH):
	@echo Making dependency directory
	@mkdir $(DEP_PATH)

$(PATH64)/%.o : src/%.cpp
	@echo Compiling $<
	@printf "  "
	g++ $< -c -Iinclude $(FLAGS) -o $@

$(PATH32)/%.o : src/%.cpp
	@echo Compiling $<
	@printf "  "
	i686-w64-mingw32-g++ $< -c -Iinclude $(FLAGS) -o $@

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
