#####################################################################
#-----------------------------------------
# This is for Linux
#
OSFLAGS = -DOS_LINUX -Dextname
CFLAGS = -g -O2 -Wall  -DSBS
LIBS = -lm -lz -lutil -lnsl -lpthread

#-----------------------------------------
# ROOT flags and libs
#
ifdef ROOTSYS
ROOTCFLAGS := $(shell  $(ROOTSYS)/bin/root-config --cflags)
ROOTCFLAGS += -DHAVE_ROOT -DUSE_ROOT
ROOTLIBS   := $(shell  $(ROOTSYS)/bin/root-config --libs) -Wl,-rpath,$(ROOTSYS)/lib
ROOTLIBS   += -lThread
endif

DIR           = $(shell pwd)

INC_DIR       = ./
SRC_DIR       = ./
LIB_DIR       = ./
BIN_DIR       = ./
DICT_DIR      = $(DIR)/../../dict
DICT_INC      = $(DICT_DIR)/include
DICT_SRC      = $(DICT_DIR)/src
DICT_LIB      = $(DICT_DIR)/lib
FUNC_DIR      = $(DIR)/../../func
FUNC_INC      = $(FUNC_DIR)/include
FUNC_SRC      = $(FUNC_DIR)/func/src
FUNC_LIB      = $(FUNC_DIR)/func/lib
#-------------------------------------------------------------------
# For Library.
DICTNAME      =  libLHCfEvent.so
#-------------------------------------------------------------------

INCALL += -I$(INC_DIR) -I$(DICT_INC) -I$(FUNC_INC)
 
####################################################################
# Lines below here should not be edited
####################################################################

LIB =  $(LIBDICT_LIBS) $(SRC_DIR)/$(LIBDICT_NAME).o 

# compiler
CC = gcc
CXX = g++

CFLAGS += -g $(INCALL)
LD       = g++
LDFLAGS +=
SOFLAGS  = -shared

PROGRAMS = simbuild simbuild_tmp darmbuild gencolbuild combine pGasbuild

all: dict $(PROGRAMS)

simbuild : simbuild.o $(DICT_LIB)/$(DICTNAME) 
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(ROOTLIBS) $(LIBS)

simbuild.o : simbuild.cpp FileToSimIncidents.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

simbuild_tmp : simbuild_tmp.o $(DICT_LIB)/$(DICTNAME) 
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(ROOTLIBS) $(LIBS)

simbuild_tmp.o : simbuild_tmp.cpp FileToSimIncidents.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@	

darmbuild : darmbuild.o $(DICT_LIB)/$(DICTNAME) 
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(ROOTLIBS) $(LIBS)

darmbuild.o : darmbuild.cpp DarmToSimIncidents.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

gencolbuild : gencolbuild.o $(DICT_LIB)/$(DICTNAME) 
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(ROOTLIBS) $(LIBS)

gencolbuild.o : gencolbuild.cpp GencolToSimIncidents.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

combine : combine.o $(DICT_LIB)/$(DICTNAME) 
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(ROOTLIBS) $(LIBS)

combine.o : combine.cpp
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

pGasbuild : pGasbuild.o $(DICT_LIB)/$(DICTNAME) 
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(ROOTLIBS) $(LIBS)

pGasbuild.o : pGasbuild.cpp
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(FUNC_SRC)/%.o  :  $(FUNC_SRC)/%.cpp  $(FUNC_SRC)/%.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(DICT_LIB)/$(DICTNAME) : dict

dict: 	
	make -C $(DICT_DIR)	

$(INC_DIR)/%.h :

clean:
	rm -f *.o */*.o */*~ *~ \#*
	rm -f $(PROGRAMS)
