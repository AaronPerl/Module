################################
####  Module Game Makefile  ####
################################

# Copyright (c) 2016, Aaron Perl
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

MAKE = make
CXX = g++

MODULE_DIR = ../..

# Retrieve variables from Module's makefile
MOD_BUILD_DIR     = $(shell cd $(MODULE_DIR) && $(MAKE) dump_build_dir64)
MOD_INTERFACES    = $(shell cd $(MODULE_DIR) && $(MAKE) dump_interfaces)
MOD_INT_DIRS      = $(shell cd $(MODULE_DIR) && $(MAKE) dump_interface_includes)
MOD_INT_BUILD_DIR = $(shell cd $(MODULE_DIR) && $(MAKE) dump_interface_dir_64)
MOD_LIB_INC_DIRS  = $(shell cd $(MODULE_DIR) && $(MAKE) dump_lib_include_dirs)
MOD_LIB_BIN_DIRS  = $(shell cd $(MODULE_DIR) && $(MAKE) dump_lib_bin_dirs)
MOD_LIBS_LINKS    = $(shell cd $(MODULE_DIR) && $(MAKE) dump_lib_links)

# Extension variables
EXTENSION_LOC = $(MODULE_DIR)/extensions
EXTENSIONS = physics

EXTENSION_DIRS     = $(addprefix $(EXTENSION_LOC)/, $(EXTENSIONS))
EXTENSION_BINARIES = $(notdir $(wildcard $(EXTENSION_DIRS)/*.a))
EXTENSION_LINKS    = $(patsubst lib%.a,-l%,$(EXTENSION_BINARIES))
EXTENSION_INCLUDES = $(addprefix -I, $(EXTENSION_DIRS))
EXTENSION_BIN_DIRS = $(addprefix -L, $(EXTENSION_DIRS))
EXTENSION_FLAGS    = $(EXTENSION_INCLUDES) $(EXTENSION_BIN_DIRS) $(EXTENSION_LINKS)

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
				
# Extra demo-specific flags
BULLET_DIR     = $(EXTENSION_LOC)/physics/bullet/bin
BULLET_LIBS    = BulletSoftBody BulletDynamics BulletCollision LinearMath
BULLET_FLAGS   = $(addprefix -l, $(BULLET_LIBS))
BULLET_FLAGS  += $(addprefix -L, $(BULLET_DIR))

EXTRA_FLAGS    = $(BULLET_FLAGS)

# C++ compiler flags
# CXX_FLAGS = -Wl,--no-as-needed -Wall -fstack-protector-all -fpic -Wstack-protector -D_FORTIFY_SOURCE=2
CXX_FLAGS = -Wall -fstack-protector-all -fpic -Wstack-protector -D_FORTIFY_SOURCE=2

# Disable this for release mode
CXX_FLAGS += -g -DDEBUG -ggdb3

.DEFAULT_GOAL = all
.PHONY : all test dump_mod_flags

all: main.exe
	
dump_mod_flags:
	@echo $(MODULE_FLAGS)
	
dump_ext_flags:
	@echo $(EXTENSION_LINKS)
	
main.exe: main.cpp
	$(CXX) $< $(CXX_FLAGS) $(MODULE_FLAGS) $(EXTENSION_FLAGS) $(EXTRA_FLAGS) -o $@