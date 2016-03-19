EASTL := lib/EASTL
EASTL_LINK := -lEASTL
EASTL_LIB  := 
EASTL_INC  := -I$(EASTL)/include

GLM = lib/glm
SDL2 = lib/SDL2-2.0.3/x86_64-w64-mingw32
SDL2_32 = $(SDL2)/../i686-w64-mingw32
GLEW = lib/glew-1.11.0
BULLET = lib/bullet3
OPENAL_SOFT = lib/openal-soft-1.16.0
FREEALUT = lib/freealut
SOIL = lib/SOIL

#LIBS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglew32 -lBulletDynamics -lBulletCollision -lLinearMath
LIBS 			:= -lalut -lSDL2main -lSDL2 -lSOIL $(EASTL_LINK)
LIB_INC_PATHS 		:= -I$(GLEW)/include -I$(SDL2)/include -I$(GLM) -I$(BULLET)/src -I$(OPENAL_SOFT)/include -I$(FREEALUT)/include -I$(SOIL)/src $(EASTL_INC)
LIB_INC_PATHS_32 	:= -I$(GLEW)/include -I$(SDL2_32)/include -I$(GLM) -I$(BULLET)/src -I$(OPENAL_SOFT)/include -I$(FREEALUT)/include -I$(SOIL)/src $(EASTL_INC)
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
TEST_PROGRAM = main_test
NULL = 

ifeq ($(OS), Windows_NT)
	TEST_PROGRAM := $(addsuffix .exe, $(TEST_PROGRAM))
	EASTL_LIB := -L$(EASTL)/build/mingw-w64
	LIB_PATHS 		+= -L$(GLEW)/lib -L$(SDL2)/lib -L$(BULLET)/lib -L$(OPENAL_SOFT)/libs/Win64 -L$(SOIL)/lib $(EASTL_LIB)
	# TODO 32 bit EASTL
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

INTERFACE_PATH = interfaces
INTERFACE_BUILD_DIR_64 = $(PATH64)/interfaces
INTERFACE_BUILD_DIR_32 = $(PATH32)/interfaces

# EX: interfaces/SDLOpenGLInterface
INTERFACE_PATHS = $(wildcard $(INTERFACE_PATH)/*)

# EX: SDLOpenGLInterface
INTERFACE_NAMES = $(notdir $(INTERFACE_PATHS))

# EX: libSDLOpenGLInterface.a
INTERFACE_FILE_NAMES = $(addprefix lib, $(addsuffix .a, $(INTERFACE_NAMES)))

# EX: build/.../interfaces/libSDLOpenGLInterface.a
INTERFACE_LIBS_64 = $(addprefix $(addsuffix /, $(INTERFACE_BUILD_DIR_64)), $(INTERFACE_FILE_NAMES))
INTERFACE_LIBS_32 = $(addprefix $(addsuffix /, $(INTERFACE_BUILD_DIR_32)), $(INTERFACE_FILE_NAMES))

# EX: -Iinterfaces/SDLOpenGLInterface
INTERFACE_INC = $(addprefix -I,$(INTERFACE_PATHS))

# EX: -Lbuild/.../interfaces
INTERFACE_LIB_PATHS_64 = $(addprefix -L, $(INTERFACE_BUILD_DIR_64))
INTERFACE_LIB_PATHS_32 = $(addprefix -L, $(INTERFACE_BUILD_DIR_32))

# EX: -lSDLOpenGLInterface
INTERFACE_LINKS = $(addprefix -l, $(INTERFACE_NAMES))


define make-interface
$(INTERFACE_BUILD_DIR_32)/%.o : $1/%.cpp $(wildcard $1/*.hpp) | $(INTERFACE_BUILD_DIR_32)
	@echo Compiling $$@
	@printf "  "
	g++ $(FLAGS) $(LIB_INC_PATHS) -Iinclude -c $$< -o $$@
$(INTERFACE_BUILD_DIR_64)/%.o : $1/%.cpp $(wildcard $1/*.hpp) | $(INTERFACE_BUILD_DIR_64)
	@echo Compiling $$@
	@printf "  "
	g++ $(FLAGS) $(LIB_INC_PATHS) -Iinclude -c $$< -o $$@
$(INTERFACE_BUILD_DIR_32)/lib$(notdir $1).a : $(addprefix $(INTERFACE_BUILD_DIR_32)/,$(notdir $(patsubst %.cpp,%.o,$(wildcard $1/*.cpp)))) | $(INTERFACE_BUILD_DIR_32)
	@echo $$@ $$^
	ar rcs $$@ $$^
$(INTERFACE_BUILD_DIR_64)/lib$(notdir $1).a : $(addprefix $(INTERFACE_BUILD_DIR_64)/,$(notdir $(patsubst %.cpp,%.o,$(wildcard $1/*.cpp)))) | $(INTERFACE_BUILD_DIR_64)
	@echo $$@ $$^
	ar rcs $$@ $$^
endef

# include $(addsuffix /Makefile, $(INTERFACE_PATHS))

.DEFAULT_GOAL = 64bit
	
# targets for dumping specific variables for use in other makefiles
.PHONY: dump_build_dir64 dump_build_dir32 \
        dump_interfaces dump_interface_includes \
        dump_interface_dir_64 dump_interface_dir_32 \
		dump_lib_include_dirs dump_lib_bin_dirs \
		dump_lib_links

dump_build_dir64:
	@echo $(PATH64)
dump_build_dir32:
	@echo $(PATH32)
dump_interfaces:
	@echo $(INTERFACE_NAMES)
dump_interface_includes:
	@echo $(INTERFACE_PATHS)
dump_interface_dir_64:
	@echo $(INTERFACE_BUILD_DIR_64)
dump_interface_dir_32:
	@echo $(INTERFACE_BUILD_DIR_32)
dump_lib_include_dirs:
	@echo $(LIB_INC_PATHS:-I%=%)
dump_lib_bin_dirs:
	@echo $(LIB_PATHS:-L%=%)
dump_lib_links:
	@echo $(LIBS)
 
.PHONY: all depends 64bit 32bit interfaces interfaces32 interfaces64 test run clean 

$(TEST_PROGRAM) : $(PATH64)/$(FULL_NAME) $(INTERFACE_LIBS_64) main_test.cpp
	@echo Compiling test program!
	@g++ main_test.cpp -Iinclude -L$(PATH64) -l$(LIBRARY_NAME) $(INTERFACE_INC) $(LIB_PATHS) $(LIB_INC_PATHS) $(INTERFACE_LIB_PATHS_64) $(INTERFACE_LINKS) $(LIBS) $(FLAGS) -o main_test

all: 64bit 32bit
depends: $(FULL_DEPS)
64bit: $(PATH64)/$(FULL_NAME)
32bit: $(PATH32)/$(FULL_NAME)
interfaces64: $(INTERFACE_LIBS_64)
interfaces32: $(INTERFACE_LIBS_32)
interfaces : interfaces32 interfaces64
test: $(TEST_PROGRAM)
run: test
	main_test
clean:
	@echo Files are: $(foreach dir, $(INTERFACE_PATHS), $(wildcard $(dir)/*.o))
	rm -rf build $(DEP_PATH) $(INTERFACE_LIBS) $(foreach dir, $(INTERFACE_PATHS), $(wildcard $(dir)/*.o))
	
$(foreach d,$(INTERFACE_PATHS),$(eval $(call make-interface,$d)))

$(INTERFACE_BUILD_DIR_64)/%/*.o : $(INTERFACE_PATHS)/%/*.hpp

$(INTERFACE_BUILD_DIR_64)/*/%.o : $(addsuffix /%.cpp, $(wildcard $(INTERFACE_PATHS)/*))
	@echo $@ $^

$(INTERFACE_BUILD_DIR_64)/%/*.a : $(INTERFACE_BUILD_DIR_64)

$(INTERFACE_BUILD_DIR_64) : 
	@mkdir $@ -p 2>$(NULL) || mkdir $(subst /,\,$@)
	
$(INTERFACE_BUILD_DIR_32) : 
	@mkdir $@ -p 2>$(NULL) || mkdir $(subst /,\,$@)

$(PATH64):
	@echo Making 64-bit build directory
	@mkdir $@ -p 2>$(NULL) || mkdir $(subst /,\,$@)

$(PATH32):
	@echo Making 32-bit build directory
	@mkdir $@ -p 2>$(NULL) || mkdir $(subst /,\,$@)

$(DEP_PATH):
	@echo Making dependency directory
	@mkdir $@

$(PATH64)/%.o : src/%.cpp
	@echo Compiling $<
	@printf "  "
	g++ $< -c -Iinclude $(EASTL_INC) $(FLAGS) -o $@

$(PATH32)/%.o : src/%.cpp
	@echo Compiling $<
	@printf "  "
	i686-w64-mingw32-g++ $< -c -Iinclude $(EASTL_INC) $(FLAGS) -o $@

$(DEP_PATH)/%.d : src/%.cpp | $(DEP_PATH)
	@echo Generating dependencies for $<
	@g++ -MM -MT $(PATH64)/$(notdir $(<:.cpp=.o)) $(FLAGS) -Iinclude $< > $@
	@g++ -MM -MT $(PATH32)/$(notdir $(<:.cpp=.o)) $(FLAGS) -Iinclude $< >> $@

$(PATH64)/$(FULL_NAME): $(FULL_OBJS64)
	ar rcs $@ $^

$(PATH32)/$(FULL_NAME): $(FULL_OBJS32)
	ar rcs $@ $^

$(FULL_OBJS64) : | $(PATH64)
$(FULL_OBJS32) : | $(PATH32)
$(FULL_DEPS) : | $(DEP_PATH)

-include $(FULL_DEPS)
