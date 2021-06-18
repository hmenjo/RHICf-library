#####################################################################
#
#  RHICf Reconstruction
#  
#  The following passes must be specified for your system 
#       LIBDIR
#       RHICF_DIR
#
#
#
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

#-----------------------------------------
# LHCf Library
#
#LIBDIR        = $(PWD)/../../
#LIBDIR        = /home/rhicf/RHICf/Analysis/RHIC/general
LIBDIR        = ../general
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
SCNAME        = libLHCfSC.so
SC_DIR        = $(LIBDIR)/sc
SC_INC        = $(SC_DIR)/include
SC_SRC        = $(SC_DIR)/src
SC_LIB        = $(SC_DIR)/lib
LHCFLIBS      = $(DICT_LIB)/$(DICTNAME) $(FUNC_LIB)/$(FUNCNAME) \
                $(SC_LIB)/$(SCNAME)
LHCFLIBS      += -Wl,-rpath,$(DICT_LIB) -Wl,-rpath,$(FUNC_LIB) -Wl,-rpath,$(SC_LIB)
#----------------------------------------------
# RHICf Library
RHICF_DIR      = ../Library
RHICF_INC      = $(RHICF_DIR)/include
RHICFLIB       = $(RHICF_DIR)/lib/libRHICf.so
RHICFLIB      += -Wl,-rpath,$(RHICF_DIR)/lib
###-------------------------------------------------------------------
# 
# For this codes
#
INC_DIR       = ./include
SRC_DIR       = ./src
BIN_DIR       = ./bin
INCALL += -I$(INC_DIR) -I$(DICT_INC) -I$(FUNC_INC) -I$(SC_INC) -I$(RHICF_INC) 
INCALL += -DLIBDIR=\"$(LIBDIR)\" -DWORKDIR=\"$(PWD)\"
CXXFLAGS += $(INCALL) 


ROOTLIBS  += -Wl,-rpath,$(ROOTSYS)/lib -lSpectrum -lEG
ROOTGLIBS += -Wl,-rpath,$(ROOTSYS)/lib

PROGRAMS = reconstruction02 checkpedelist

all: $(PROGRAMS)

reconstruction02 : $(SRC_DIR)/reconstruction02.o $(SRC_DIR)/A1Calibration.o $(SRC_DIR)/A1Reconstruction.o $(SRC_DIR)/ScintiPosDepGSO.o $(SRC_DIR)/GSObarPosCalc.o 
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS) $(RHICFLIB)

src/reconstruction02.o :$(INC_DIR)/A1Calibration.h   $(INC_DIR)/A1Reconstruction.h 

checkpedelist : $(SRC_DIR)/checkpedelist.o 
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS) $(RHICFLIB)

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(INC_DIR)/%.h :

clean:
	rm -f *.o */*.o */*~ *~ \#*
	rm -f $(BIN_DIR)/reconstruction02 




