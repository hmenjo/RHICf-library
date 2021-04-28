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
LIBDIR = $(PWD)/../../
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
#
#-------------------------------------------------------------------
# 
# For this codes
#
INC_DIR       = ./include
SRC_DIR       = ./src
BIN_DIR       = ./
INCALL += -I$(DICT_INC) -I$(FUNC_INC) -I$(SC_INC) 
INCALL += -I$(INC_DIR)

CXXFLAGS +=  $(INCALL) -DLHCFLIBBASE=\"$(LIBDIR)\"

ROOTLIBS  += -Wl,-rpath,$(ROOTSYS)/lib
ROOTGLIBS += -Wl,-rpath,$(ROOTSYS)/lib

PROGRAMS = LHCfroot.exe

all: $(PROGRAMS) slink

LHCfroot.exe : src/LHCfroot.o src/LHCfrootFunctions.o src/libLHCfrootFunctions.o
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^ \
	$(LIBS) $(ROOTLIBS) $(LHCFLIBS) 

$(SRC_DIR)/libLHCfrootFunctions.cpp : $(INC_DIR)/LHCfrootFunctions.h \
	                              $(INC_DIR)/LinkDef.h
	rootcint -f libLHCfrootFunctions.cpp -c -I$(INC_DIR) -I$(SRC_DIR) \
	-I$(DICT_INC) -I$(FUNC_INC) -I$(SC_INC) \
	LHCfrootFunctions.h $(INC_DIR)/LinkDef.h
	mv libLHCfrootFunctions.h   $(INC_DIR)/
	mv libLHCfrootFunctions.cpp $(SRC_DIR)/

slink : LHCfroot.exe
	rm -f LHCfroot
	ln -s LHCfroot.exe LHCfroot
	cd ../../bin/ ; \
	rm -f  ./LHCfroot ; \
	ln -s  ../Tools/LHCfroot/LHCfroot.exe ./LHCfroot

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp  $(INC_DIR)/%.h
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(SRC_DIR)/%.o  :  $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(OSFLAGS) -c $< -o $@

$(INC_DIR)/%.h :

clean:
	rm -f *.o */*.o */*~ *~ \#*
	rm -f $(INC_DIR)/libLHCfrootFunctions.h $(SRC_DIR)/libLHCfrootFunctions.cpp
	rm -f $(PROGRAMS)
