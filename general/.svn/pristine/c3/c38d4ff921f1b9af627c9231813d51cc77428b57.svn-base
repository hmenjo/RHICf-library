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
FUNC_SRC      = $(FUNC_DIR)/src
FUNC_LIB      = $(FUNC_DIR)/lib
#-------------------------------------------------------------------
# For Library.
DICTNAME      =  libLHCfEvent.so
FUNCNAME      =  libLHCfFunction.so
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

all: dict sample_eventloop sample_eventselection

sample_eventloop : sample_eventloop.o $(DICT_LIB)/$(DICTNAME) 
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(ROOTLIBS) $(LIBS)

sample_eventloop.o : sample_eventloop.cpp
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

sample_eventselection : sample_eventselection.o $(DICT_LIB)/$(DICTNAME) 
	$(CXX) $(CFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(ROOTLIBS) $(LIBS)

sample_eventselection.o : sample_eventselection.cpp
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(FUNC_SRC)/%.o  :  $(FUNC_SRC)/%.cpp  $(FUNC_SRC)/%.h
	$(CXX) $(CFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(DICT_LIB)/$(DICTNAME) : dict

$(FUNC_LIB)/$(FUNCNAME) : dict

dict:
	make -C $(DICT_DIR)
	make -C $(FUNC_DIR)

$(INC_DIR)/%.h :

clean:
	rm -f *.o */*.o */*~ *~ \#*
	rm -f sample_eventloop sample_eventselection