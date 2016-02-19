MAKE = make
CXX = g++

MODULE_DIR = ../..

# Retrieve variables from Module makefile
MOD_BUILD_DIR     = $(shell cd $(MODULE_DIR) && $(MAKE) dump_build_dir64)
MOD_INTERFACES    = $(shell cd $(MODULE_DIR) && $(MAKE) dump_interfaces)
MOD_INT_DIRS      = $(shell cd $(MODULE_DIR) && $(MAKE) dump_interface_includes)
MOD_INT_BUILD_DIR = $(shell cd $(MODULE_DIR) && $(MAKE) dump_interface_dir_64)
MOD_LIB_INC_DIRS  = $(shell cd $(MODULE_DIR) && $(MAKE) dump_lib_include_dirs)
MOD_LIB_BIN_DIRS  = $(shell cd $(MODULE_DIR) && $(MAKE) dump_lib_bin_dirs)
MOD_LIBS_LINKS    = $(shell cd $(MODULE_DIR) && $(MAKE) dump_lib_links)

# Create compiler flags for including and linking Module
MOD_INCLUDES = -I$(MODULE_DIR)/include
MOD_LINKS    = -lModule

MOD_INCLUDES += $(addprefix -I$(MODULE_DIR)/, $(MOD_INT_DIRS))
MOD_INCLUDES += $(addprefix -I$(MODULE_DIR)/, $(MOD_LIB_INC_DIRS))
MOD_LIB_DIRS  = $(addprefix -L$(MODULE_DIR)/, $(MOD_LIB_BIN_DIRS))
MOD_LINKS    += $(addprefix -l, $(MOD_INTERFACES))


MODULE_FLAGS  = $(MOD_INCLUDES) \
                $(MOD_LIB_DIRS) -L$(MODULE_DIR)/$(MOD_BUILD_DIR) -L$(MODULE_DIR)/$(MOD_INT_BUILD_DIR) \
				$(MOD_LINKS) $(MOD_LIBS_LINKS)

# C++ compiler flags
CXX_FLAGS = -Wl,--no-as-needed -Wall -fstack-protector-all -fpic -Wstack-protector -D_FORTIFY_SOURCE=2

# Disable this for release mode
CXX_FLAGS += -g -DDEBUG -ggdb3

.DEFAULT_GOAL = all
.PHONY : all test dump_mod_flags

all: main.exe
	
dump_mod_flags:
	@echo $(MODULE_FLAGS)
	
main.exe: main.cpp
	$(CXX) $(CXX_FLAGS) $(MODULE_FLAGS) $< -o $@