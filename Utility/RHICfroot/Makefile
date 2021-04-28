#####################################################################
#------------------------------------------------
#
# Configuration for each architecture
# (Updated for  ROOT version > 5.32)

MAKEARCH        :=      $(shell find $(ROOTSYS)/test -name Makefile.arch)
ifeq ($(MAKEARCH), )
# 41594 or later
MAKEARCH        :=      $(shell find $(ROOTSYS)/etc -name Makefile.arch)
endif

include $(MAKEARCH)

# For MAC OS X users
ifneq (,$(filter $(ARCH),macosx macosx64))
SOFLAGS  += -install_name $(LIB_DIR)/$(LIBNAME).so
endif
#
#------------------------------------------------
# LHCf Library
LIBDIR = $(PWD)/../../general
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
LHCFLIBS      += -Wl,-rpath,$(DICT_LIB) -Wl,-rpath,$(FUNC_LIB) 

#------------------------------------------------
# RHICf Library
RHICF_DIR  = $(PWD)/../../Library
RHICF_INC  = $(RHICF_DIR)/include
RHICF_SRC  = $(RHICF_DIR)/src
RHICF_LIB  = $(RHICF_DIR)/lib
RHICF_NAME = libRHICf.so

RHICFLIBS  = $(RHICF_LIB)/$(RHICF_NAME)
RHICFLIBS  += -Wl,-rpath,$(RHICF_LIB)
#-------------------------------------------------------------------
# 
# For this codes
#
INC_DIR       = ./include
SRC_DIR       = ./src
BIN_DIR       = ./
INCALL += -I$(DICT_INC) -I$(FUNC_INC)  
INCALL += -I$(RHICF_INC)
INCALL += -I$(INC_DIR)

CXXFLAGS +=  $(INCALL) -DPATHBASE=\"$(PWD)/../../\"

ROOTLIBS  += -Wl,-rpath,$(ROOTSYS)/lib -lEG
ROOTGLIBS += -Wl,-rpath,$(ROOTSYS)/lib -lEG

PROGRAMS = RHICfroot

all: $(PROGRAMS) 

RHICfroot : src/RHICfroot.o src/RHICfrootFunctions.o src/libRHICfrootFunctions.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS) $(RHICFLIBS) 

$(SRC_DIR)/libRHICfrootFunctions.cpp : $(INC_DIR)/RHICfrootFunctions.h \
	                              $(INC_DIR)/LinkDef.h
	rootcint -f libRHICfrootFunctions.cpp -c -I$(INC_DIR) -I$(SRC_DIR) \
	-I$(DICT_INC) -I$(FUNC_INC) -I$(RHICF_INC) \
	RHICfrootFunctions.h $(INC_DIR)/LinkDef.h
	mv libRHICfrootFunctions.h   $(INC_DIR)/
	mv libRHICfrootFunctions.cpp $(SRC_DIR)/

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(INC_DIR)/%.h :

clean:
	rm -f *.o */*.o */*~ *~ \#*
	rm -f $(INC_DIR)/libRHICfrootFunctions.h $(SRC_DIR)/libRHICfrootFunctions.cpp
	rm -f $(PROGRAMS)
