################################
## Module Extension Makefile  ##
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

EXTENSION_NAME := ModulePhysicsExt

################################
######    Module Flags    ######
################################

# Location of Module relative to this directory
MODULE_DIR := ../..

# Module include directory
MODULE_INC := $(MODULE_DIR)/include

################################
###### External Libraries ######
################################

# Arguments:
#  1: file
#  2: variable name
#  3: variable value (output)
define readLine
  GREP_PATTERN := $(2)[ \t]*=[ \t]*
  SED_PATTERN := /$(GREP_PATTERN)/s/$(GREP_PATTERN)//p
  $(3) = (shell grep -P "$(GREP_PATTERN)" $(1) | sed -n "$(SED_PATTERN)")
endef
  
#define readConfig
#  GREP_PATTERN := 
#  SED_PATTERN := 
#  $(2) := 
#  $(3) :=
#  $(4) :=
#  $(5) :=
#endef

#$(call readLine, build.txt, inc_dirs, $(test_value))

# External library directories
BULLET_DIR  := bullet

# External library include directories
LIB_INC := $(MODULE_DIR)/lib/EASTL/include $(MODULE_DIR)/lib/EASTL/test/packages/EABase/include/Common $(BULLET_DIR)/src

# External library binary directories
LIB_BINS := $(BULLET_DIR)/bin

# External libraries to link
LIBS := BulletSoftBody BulletDynamics BulletCollision LinearMath

# Generate linker flags from list of libraries
LINKS := $(addprefix -l, $(LIBS))

################################
###### Implicit Variables ######
################################

# C++ Compiler
CXX = g++

# C Compiler
CC = gcc

# Archiver
AR = ar

# Flags for C/C++ compilers
CPPFLAGS := -MMD -MP -Wall -I$(MODULE_INC)
CPPFLAGS += $(addprefix -I, $(LIB_INC))
CPPFLAGS += $(addprefix -L, $(LIB_BINS))
CPPFLAGS += $(LINKS)

# Flags for C++ Compilers
CXXFLAGS :=

# Flags for C Compilers
CFLAGS :=

# Flags for archiver
ARFLAGS := rcs

################################
######  Derived Variables ######
################################

CXX_FILES    := $(wildcard *.cpp)
C_FILES      := $(wildcard *.c)
OBJECTS      := $(CXX_FILES:.cpp=.o) $(C_FILES:.c=.o)
DEPS         := $(OBJECTS:.o=.d)
HEADER_FILES := $(wildcard *.h) $(wildcard *.hpp)
EXTENSION = lib$(EXTENSION_NAME).a

################################
######      Targets       ######
################################

-include $(DEPS)

.DEFAULT_GOAL = all

.PHONY : all clean test

all : $(EXTENSION)

$(EXTENSION) : $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

say_stuff:
	echo $(testvalue)