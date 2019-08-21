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
# LHCf Library (Give to the pass for Library)
LIBDIR = /crhome/sato.kenta/RHICf/Analysis/Op2017/general
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
#
#-------------------------------------------------------------------
# 
# For this codes
#
INC_DIR       = ./
SRC_DIR       = ./
BIN_DIR       = ./
INCALL += -I$(DICT_INC) -I$(FUNC_INC) 
INCALL += -I$(INC_DIR)

CXXFLAGS +=  $(INCALL) -DLHCFLIBBASE=\"$(LIBDIR)\"

ROOTLIBS  += -Wl,-rpath,$(ROOTSYS)/lib
ROOTGLIBS += -Wl,-rpath,$(ROOTSYS)/lib

PROGRAMS = sample_eventloop sample_eventloop2

all: $(PROGRAMS) 

sample_eventloop : $(SRC_DIR)/sample_eventloop.cpp 
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS) 

sample_eventloop2 : $(SRC_DIR)/sample_eventloop2.cpp 
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS) 

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(INC_DIR)/%.h :

clean:
	rm -f $(SRC_DIR)/*.o 
	rm -f $(PROGRAMS)
