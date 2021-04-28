#####################################################################
#-----------------------------------------
# This is for Linux
#
OSFLAGS = -DOS_LINUX -Dextname
CFLAGS = -g -O2 -Wall  -DSBS
LIBS = -lm -lz -lutil -lnsl -lpthread
#
#-----------------------------------------
# ROOT flags and libs
#
ifdef ROOTSYS
ROOTCFLAGS := $(shell  $(ROOTSYS)/bin/root-config --cflags)
ROOTCFLAGS += -DHAVE_ROOT -DUSE_ROOT
ROOTLIBS   := $(shell  $(ROOTSYS)/bin/root-config --libs) -Wl,-rpath,$(ROOTSYS)/lib
ROOTLIBS   += -lThread
ROOTGLIBS  := $(shell root-config --glibs)
endif
#
#-----------------------------------------
# LHCf Library
#
ifdef LHCF_LIBDIR
   LIBDIR = $(LHCF_LIBDIR)
else
   LIBDIR = $(HOME)/LHCf/Analysis/LHC/general
endif
DICTNAME      = libLHCfEvent.so
DICT_DIR      = $(LIBDIR)/dict
DICT_INC      = $(DICT_DIR)/include
DICT_SRC      = $(DICT_DIR)/src
DICT_LIB      = $(DICT_DIR)/lib
FUNCNAME      = libLHCfFunction.so
FUNC_DIR      = $(LIBDIR)/func
FUNC_INC      = $(FUNC_DIR)/include
FUNC_SRC      = $(FUNC_DIR)/src
FUNC_LIB      = $(FUNC_DIR)/lib
LHCFLIBS      = $(DICT_LIB)/$(DICTNAME) $(FUNC_LIB)/$(FUNCNAME)
#
#-----------------------------------------
# 
# For this codes
#
BIN_DIR       = ./
INCALL += -I$(DICT_INC) -I$(FUNC_INC) -I./include 

# compiler
CC = gcc
CXX = g++
CFLAGS += -g $(INCALL)
LD       = g++
LDFLAGS +=
SOFLAGS  = -shared

TARGETS = EventSelection

all: $(TARGETS)


EventSelection :  EventSelection.o
	$(CXX) $(CFLAGS) -o $@ $^ \
	$(LIBS) $(ROOTLIBS) $(ROOTGLIBS) $(LHCFLIBS) 

%.o	:   %.cpp 
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

src/%.o  :  src/%.cpp  src/%.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

src/%.o  :  src/%.cpp
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@


clean:
	rm -f *.o */*.o */*~ *~ \#*
	rm -f $(TARGETS)
